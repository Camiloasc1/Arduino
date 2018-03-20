#include <AccelStepper.h>

const int PIN_BUZZER = 7;
const int DELAY_FEED_CYCLE = 5 * 1000;

AccelStepper stepper(AccelStepper::FULL4WIRE, 8, 10, 9, 11); // For 28BYJ-48 swap pins 2 and 3

const int BEGIN_MELODY_LENGTH = 12;
// Melody in Hz
int beginMelodyFreq[] = {
  775, 0, 775, 0, 775, 0, 775, 0, 775, 0, 775, 0
};
// Duration in milliseconds
int beginMelodyDurations[] = {
  100, 100, 200, 1000, 100, 100, 200, 1000, 100, 100, 200, 1000
};

const int END_MELODY_LENGTH = 6;
// Melody in Hz
int endMelodyFreq[] = {
  775, 0, 775, 0, 775, 0
};
// Duration in milliseconds
int endMelodyDurations[] = {
  100, 100, 100, 100, 100, 100
};

const int FEEDING_TONE = 500;
const int FEEDING_TONE_DURATION = 500;

void setup()
{
  pinMode(PIN_BUZZER, OUTPUT);

  stepper.setMaxSpeed(1024);
  stepper.setAcceleration(256);
}

void loop()
{
  // Begin alarm
  for (int note = 0; note < BEGIN_MELODY_LENGTH; note++) {
    tone(PIN_BUZZER, beginMelodyFreq[note], beginMelodyDurations[note]);
    delay(beginMelodyDurations[note]);
  }

  // Feeding alarm
  unsigned long toneBegin = millis();
  tone(PIN_BUZZER, FEEDING_TONE, FEEDING_TONE_DURATION);

  // Turn once
  stepper.move(2048);
  stepper.enableOutputs();
  while (stepper.distanceToGo() != 0) {
    // Run the motor
    stepper.run();

    // Feeding alarm
    if (millis() - toneBegin > 2 * FEEDING_TONE_DURATION) {
      toneBegin = millis();
      tone(PIN_BUZZER, FEEDING_TONE, FEEDING_TONE_DURATION);
    }
  }
  stepper.disableOutputs();

  while (millis() - toneBegin < 2 * FEEDING_TONE_DURATION) {
    delay(1);
  }

  // End alarm
  for (int note = 0; note < END_MELODY_LENGTH; note++) {
    tone(PIN_BUZZER, endMelodyFreq[note], endMelodyDurations[note]);
    delay(endMelodyDurations[note]);
  }

  // Wait until the next feed cycle
  delay(DELAY_FEED_CYCLE);
}

