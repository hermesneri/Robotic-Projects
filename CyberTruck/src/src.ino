// #include "../libs/motorControl/motorControl.h"
#include <Arduino.h>

#define FRONT 1
#define BACK 2
#define STOP 0

#define MOTOR_RIGHT 1
#define MOTOR_LEFT 2
#define MOTOR_BOTH 3

// Pinos do motor DC
const int pin_a = 5;
const int pin_b = 4;
const int pin_c = 7;
const int pin_d = 6;

void initMotorDc()
{
  pinMode(pin_a, OUTPUT);
  pinMode(pin_b, OUTPUT);
  pinMode(pin_c, OUTPUT);
  pinMode(pin_d, OUTPUT);
}

// direction: 0 - break, 1 - forward, 2 - backward
void setMotorDc(int motor_number = MOTOR_BOTH, int direction = FRONT)
{
  if (motor_number == MOTOR_RIGHT)
  {
    switch (direction)
    {
    case STOP:
      digitalWrite(pin_a, LOW);
      digitalWrite(pin_b, LOW);
      break;
    case FRONT:
      digitalWrite(pin_a, HIGH);
      digitalWrite(pin_b, LOW);
      break;
    case BACK:
      digitalWrite(pin_a, LOW);
      digitalWrite(pin_b, HIGH);
      break;
    }
  }
  else if (motor_number == MOTOR_LEFT)
  {
    switch (direction)
    {
    case STOP:
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      break;
    case FRONT:
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      break;
    case BACK:
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
      break;
    }
  }
  else if (motor_number == MOTOR_BOTH)
  {
    switch (direction)
    {
    case STOP:
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      break;
    case FRONT:
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      break;

    case BACK:
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
      break;
    }
  }
}

void demoMode()
{
  setMotorDc(MOTOR_BOTH, FRONT);
  delay(3000);

  setMotorDc(MOTOR_BOTH, STOP);
  delay(1000);

  setMotorDc(MOTOR_BOTH, BACK);
  delay(2000);

  setMotorDc(MOTOR_BOTH, STOP);
  delay(1000);

  setMotorDc(MOTOR_RIGHT, FRONT);
  delay(2000);

  setMotorDc(MOTOR_BOTH, STOP);
  delay(1000);

  setMotorDc(MOTOR_LEFT, FRONT);
  delay(2000);

  setMotorDc(MOTOR_BOTH, STOP);
  delay(1000);

  setMotorDc(MOTOR_RIGHT, BACK);
  delay(2000);

  setMotorDc(MOTOR_BOTH, STOP);
  delay(1000);

  setMotorDc(MOTOR_LEFT, BACK);
  delay(2000);

  setMotorDc(MOTOR_BOTH, STOP);
  delay(1000);
}

void setup()
{
  initMotorDc();
  delay(1000);
}

void loop()
{
  demoMode();
}