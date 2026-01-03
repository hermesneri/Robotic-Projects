#include <Arduino.h>
#include "MotorControl.h"

void setup()
{
  MotorControl::setMotorPin(5, 6, 9, 10);
  delay(1000);
}

void loop()
{
  MotorControl::demoMode();
}