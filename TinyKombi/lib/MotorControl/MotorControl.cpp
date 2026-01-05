/**
 * @file MotorControl.cpp
 * @author Hermes Neri (@hermesneri)
 * @brief Library to control DC motors using H-Bridge
 * @version 1.0
 * @date Jan-2026
 *
 */

#define FRONT 1
#define BACK 2
#define STOP 0

#define MOTOR_RIGHT 1
#define MOTOR_LEFT 2
#define MOTOR_BOTH 3

#include "MotorControl.h"
#include <Arduino.h>

int MotorControl::pin_a = 0;
int MotorControl::pin_b = 0;
int MotorControl::pin_c = 0;
int MotorControl::pin_d = 0;

bool MotorControl::init_dc_motor = false;

bool MotorControl::setMotorPin(int pin_a_set, int pin_b_set, int pin_c_set, int pin_d_set)
{
  pin_a = pin_a_set;
  pin_b = pin_b_set;
  pin_c = pin_c_set;
  pin_d = pin_d_set;

  pinMode(pin_a, OUTPUT);
  pinMode(pin_b, OUTPUT);
  pinMode(pin_c, OUTPUT);
  pinMode(pin_d, OUTPUT);

  init_dc_motor = true;
  MotorControl::controlMotorDc(MOTOR_BOTH, STOP);
  return true;
}

// direction: 0 - break, 1 - forward, 2 - backward
void MotorControl::controlMotorDc(int motor_number, int direction)
{
  if (!init_dc_motor)
  {
    return;
  }

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
      digitalWrite(pin_c, LOW);
      digitalWrite(pin_d, LOW);
      break;
    case FRONT:
      digitalWrite(pin_c, HIGH);
      digitalWrite(pin_d, LOW);
      break;
    case BACK:
      digitalWrite(pin_c, LOW);
      digitalWrite(pin_d, HIGH);
      break;
    }
  }
  else if (motor_number == MOTOR_BOTH)
  {
    switch (direction)
    {
    case STOP:
      digitalWrite(pin_a, LOW);
      digitalWrite(pin_b, LOW);
      digitalWrite(pin_c, LOW);
      digitalWrite(pin_d, LOW);
      break;
    case FRONT:
      digitalWrite(pin_a, HIGH);
      digitalWrite(pin_b, LOW);
      digitalWrite(pin_c, HIGH);
      digitalWrite(pin_d, LOW);
      break;

    case BACK:
      digitalWrite(pin_a, LOW);
      digitalWrite(pin_b, HIGH);
      digitalWrite(pin_c, LOW);
      digitalWrite(pin_d, HIGH);
      break;
    }
  }
}

void MotorControl::demoMode()
{
  controlMotorDc(MOTOR_BOTH, FRONT);
  delay(3000);

  controlMotorDc(MOTOR_BOTH, STOP);
  delay(1000);

  controlMotorDc(MOTOR_BOTH, BACK);
  delay(2000);

  controlMotorDc(MOTOR_BOTH, STOP);
  delay(1000);

  controlMotorDc(MOTOR_RIGHT, FRONT);
  delay(2000);

  controlMotorDc(MOTOR_BOTH, STOP);
  delay(1000);

  controlMotorDc(MOTOR_LEFT, FRONT);
  delay(2000);

  controlMotorDc(MOTOR_BOTH, STOP);
  delay(1000);

  controlMotorDc(MOTOR_RIGHT, BACK);
  delay(2000);

  controlMotorDc(MOTOR_BOTH, STOP);
  delay(1000);

  controlMotorDc(MOTOR_LEFT, BACK);
  delay(2000);

  controlMotorDc(MOTOR_BOTH, STOP);
  delay(1000);
}