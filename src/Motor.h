#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
public:
      Motor(int pwm_pin);
      Motor(int forward_pin, int reverse_pin);
      void on();
      void off();
      void forward();
      void reverse();
      void toggleDirection();
      bool isOn();
      bool isOff();
      bool isForward();
      bool isReverse();
      int getSpeed();
      void setSpeed(int value);
private:
      void update();
      void _setMotor(int pin_off, int pin_on);
      int _forward_pin;
      int _reverse_pin;
      bool _bidirectional    = false;
      bool _is_on            = false;
      bool _is_forward       = false;
      int _speed             = 0;
};
#endif
