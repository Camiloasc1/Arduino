const int PIN_BUZZER = 8;
const int sirenPeriodms = 2000;
const int sirenStepms = 1;
const float sirenSteps = sirenPeriodms / sirenStepms / 2;
const int sirenFreqMin = 500;
const int sirenFreqMax = 1200;
const float sirenFreqStep = (sirenFreqMax - sirenFreqMin) / sirenSteps;

void setup() {
  // Serial.begin(9600);
  // Serial.println(0);
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {
  float freq;

  // Ramp up
  for (int i = 0; i < sirenSteps; i++) {
    freq = sirenFreqMin + sirenFreqStep * i;
    tone(PIN_BUZZER, freq);
    delay(sirenStepms);
    // noTone(PIN_BUZZER);
  }

  // Ramp down
  for (int i = 0; i < sirenSteps; i++) {
    freq = sirenFreqMax - sirenFreqStep * i;
    tone(PIN_BUZZER, freq);
    delay(sirenStepms);
    // noTone(PIN_BUZZER);
  }
}

