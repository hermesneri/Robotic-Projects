#pragma once

class MotorControl
{
public:
  static bool setMotorPin(int pin_a_set, int pin_b_set, int pin_c_set, int pin_d_set);
  static void controlMotorDc(int motor_number = 3, int direction = 1);
  static void demoMode();

private:
  // Pins DC Motor - bridge H
  static int pin_a;
  static int pin_b;
  static int pin_c;
  static int pin_d;

  static bool init_dc_motor;
};