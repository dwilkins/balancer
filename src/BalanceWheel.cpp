#include <Arduino.h>
#include "BalanceWheel.hpp"

void setup_step() {
  pinMode(L_STK_MODE_PIN, OUTPUT);
  pinMode(L_STK_CLOCK_PIN, OUTPUT);
  pinMode(L_STK_CWB_PIN, OUTPUT);
  pinMode(L_STK_ENABLE_PIN, OUTPUT);

  pinMode(R_STK_MODE_PIN, OUTPUT);
  pinMode(R_STK_CLOCK_PIN, OUTPUT);
  pinMode(R_STK_CWB_PIN, OUTPUT);
  pinMode(R_STK_ENABLE_PIN, OUTPUT);

  digitalWrite(L_STK_ENABLE_PIN, 0);
  digitalWrite(R_STK_ENABLE_PIN, 0);

  digitalWrite(L_STK_MODE_PIN, 1);
  digitalWrite(L_STK_CLOCK_PIN, 0);
  digitalWrite(L_STK_CWB_PIN, 0);

  digitalWrite(R_STK_MODE_PIN, 1);
  digitalWrite(R_STK_CLOCK_PIN, 0);
  digitalWrite(R_STK_CWB_PIN, 1);

  delay(1);
  digitalWrite(L_STK_ENABLE_PIN, 1);
  digitalWrite(R_STK_ENABLE_PIN, 1);

}

void step_it() {
  static unsigned long next_time = 0;
  static unsigned long steps = 0;
  static int direction = 1;
  static int min_ramp_millis = 5;
  static int max_ramp_millis = 90;
  static int ramp_millis = 90;
  unsigned long current_time = millis();
  if(current_time < next_time) {
    digitalWrite(STK_LED_PIN, 0);
    return;
  }
  digitalWrite(STK_LED_PIN, 1);
  steps++;
  if(!(steps % 800)) {
    direction = 0-direction;
    digitalWrite(L_STK_CWB_PIN, (direction > 0 ? 1 : 0));
    digitalWrite(R_STK_CWB_PIN, (direction > 0 ? 0 : 1));
    next_time = current_time + 5000;
    ramp_millis = max_ramp_millis;
  } else {
    next_time = current_time + ramp_millis;
  }
  if(ramp_millis > min_ramp_millis) {
    ramp_millis -= 1;
  }
  digitalWrite(L_STK_CLOCK_PIN,1);
  digitalWrite(R_STK_CLOCK_PIN,1);
  delayMicroseconds(21);
  digitalWrite(L_STK_CLOCK_PIN,0);
  digitalWrite(R_STK_CLOCK_PIN,0);
  // digitalWrite(STK_ENABLE_PIN, 0);
  // delayMicroseconds(20);
  // digitalWrite(STK_ENABLE_PIN, 1);

}


void BalanceWheel::init() {
  pinMode(_mode_pin, OUTPUT);
  pinMode(_clock_pin, OUTPUT);
  pinMode(_enable_pin, OUTPUT);
  pinMode(_cwb_pin, OUTPUT);

  digitalWrite(L_STK_ENABLE_PIN, 0);


  digitalWrite(_mode_pin, 1);
  digitalWrite(_clock_pin, 0);
  direction( _direction );
  delay(1);
  digitalWrite(L_STK_ENABLE_PIN, 1);

}

void BalanceWheel::keep_stepping(unsigned long int steps) {
  _target_steps = (_target_steps - _current_steps) + steps;
  _current_steps = 0;
}

void BalanceWheel::step(unsigned long int steps) {
  _target_steps = steps;
  _current_steps = 0;
  /* TODO - start stepping */
}

void BalanceWheel::stop() {
  _next_hardware_task = NONE;
  _target_steps = 0;
}


bool BalanceWheel::is_running() {
  return (_target_steps);
}




void BalanceWheel::direction(enum motor_direction direction) {
  _direction = direction;
  if(_axel_side == RIGHT) {
    if(direction == FORWARD){
      digitalWrite(_cwb_pin, REVERSE );
    } else {
      digitalWrite(_cwb_pin, FORWARD);
    }
  } else {
    digitalWrite(_cwb_pin,_direction);
  }
}

bool BalanceWheel::canRun(uint32_t now) {
  return (_next_step_time && (now >= _next_step_time));
}

void BalanceWheel::run(uint32_t now) {
  switch(_next_hardware_task) {
  case NONE:
    return;
  case CLOCK_LOW:
    clock_low();
    break;
  case CLOCK_HIGH:
    clock_high();
    break;
  }

}

void BalanceWheel::clock_low() {
  digitalWrite(_clock_pin,0);
  _next_hardware_task = CLOCK_LOW;
}

void BalanceWheel::clock_high() {
  digitalWrite(_clock_pin,1);
  _next_hardware_task = CLOCK_LOW;
}
