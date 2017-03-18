#include <Arduino.h>
#include <Motor.h>

// constructor
Motor::Motor(int pwm_pin){
  _forward_pin   = pwm_pin;
  _bidirectional = false;
  pinMode(_forward_pin, OUTPUT);
  off();
}

// overloaded constructor for bidirectional control
Motor::Motor(int forward_pin, int reverse_pin){
  _forward_pin    = forward_pin;
  _reverse_pin    = reverse_pin;
  _bidirectional  = true;
  pinMode(_forward_pin, OUTPUT);
  pinMode(_reverse_pin, OUTPUT);
  off();
}

void Motor::on() { // default: true
  setSpeed(255);
}

void Motor::off() { // default: true
  setSpeed(0);
}

void Motor::forward() {
  if(_bidirectional) {
    _is_forward = true;
  }
}

void Motor::reverse() {
  if(_bidirectional) {
    _is_forward = false;
  }
}

void Motor::update(){
  _is_on = _speed > 0;
  if(_bidirectional){
    if(isForward()){
      _setMotor(_reverse_pin,_forward_pin);
    }
    else{
      _setMotor(_forward_pin,_reverse_pin);
    }
  }
  else{
    analogWrite(_forward_pin,_speed);
  }
}

void Motor::_setMotor(int pin_off, int pin_on){
  digitalWrite(pin_off, LOW);
  analogWrite(pin_on,_speed);
}

bool Motor::isForward() {
  return _is_forward;
}

bool Motor::isReverse() {
  return !_is_forward;
}

void Motor::toggleDirection() {
  if(_bidirectional) {
    _is_forward = !_is_forward;
  }
}

bool Motor::isOn() {
  return _is_on;
}

bool Motor::isOff() {
  return !_is_on;
}

int Motor::getSpeed() {
  return _speed;
}

int Motor::getSpeedPercent() {
  return int((getSpeed() / 255.0 * 100) + 0.5); // add 0.5 for correct rounding
}

void Motor::setSpeed(int value) { // default: true
  _speed = constrain(value, 0, 255);
  update();
}

void Motor::setSpeedPercent(int value) { // default: true
  setSpeed(int(value / 100.0 * 255));
}