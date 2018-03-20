#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::FULL4WIRE, 8, 10, 9, 11); // For 28BYJ-48 swap pins 2 and 3

void setup()
{
  Serial.begin(9600);
  stepper.setMaxSpeed(1024);
  stepper.setAcceleration(128);
  stepper.moveTo(1024);
}

void loop()
{
  // Change direction at the limit
  if (stepper.distanceToGo() == 0) {
    Serial.println("Change");
    Serial.println(stepper.currentPosition());
    stepper.disableOutputs();
    delay(5000);
    stepper.enableOutputs();
    stepper.moveTo(-stepper.currentPosition());
  }
  stepper.run();
}
