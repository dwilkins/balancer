/*
 * BalanceWheel.hpp
 *
 * Class for handling one side of a stepper axel
 *
 * (C) Copyright 2013
 * David H. Wilkins  <dwilkins@conecuh.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 **
 ** Assumes this wheel is controlled by a stk672-330 stepper controller
 **
 ** Left side turns normally
 ** Right side is the reverse direction
 ** Originally developed to carry a balancing robot
 **
 **
 */

#ifndef BALANCEWHEEL_HPP
#define BALANCEWHEEL_HPP


#include "Task.hpp"

// 40 - 34
// left
#define L_STK_MODE_PIN 8
#define L_STK_CLOCK_PIN 9
#define L_STK_CWB_PIN 7
#define L_STK_ENABLE_PIN 6

// right
#define R_STK_MODE_PIN 11
#define R_STK_CLOCK_PIN 10
#define R_STK_CWB_PIN 12
#define R_STK_ENABLE_PIN A0

#define STK_LED_PIN 13

#define MINIMUM_STEP_DELAY 5

#define FORWARD_DIRECTION 0


// Lets make up our own numbering system for angular representations:

/*
 * 1000 0000 0000 = 180 degrees
 * 0100 0000 0000 =  90 degrees
 * 0010 0000 0000 =  45 degrees
 * 0001 0000 0000 =  22.5 degrees
 * 0000 1000 0000 =  11.25 degrees
 * 0000 0100 0000 =   5.625 degrees
 * 0000 0010 0000 =   2.8125 degrees
 * 0000 0001 0000 =   1.40625 degrees
 * 0000 0000 1000 =   0.703125
 * 0000 0000 0100 =   0.3515625
 * 0000 0000 0010 =   0.17578125
 * 0000 0000 0001 =   0.087890625
 */



void setup_step();
void step_it();

class BalanceWheel: public Task {
public:
  enum motor_direction {FORWARD=0,REVERSE=1};
  enum axel_side {LEFT, RIGHT, UNKNOWN};
  enum hardware_task {NONE, CLOCK_HIGH, CLOCK_LOW};

  BalanceWheel(int mode_pin, int clock_pin, int cwb_pin, int enable_pin,
               enum axel_side axel_side = UNKNOWN,
               int wheel_diameter_mm = 10,
               int steps_per_revolution = 200) {
    _mode_pin = mode_pin;
    _clock_pin = clock_pin;
    _cwb_pin = cwb_pin;
    _enable_pin = _enable_pin;
    _axel_side = axel_side;
    _wheel_diameter_mm = wheel_diameter_mm;
    _steps_per_revolution = steps_per_revolution;
    _direction = FORWARD;
    _next_hardware_task = NONE;
    init();
  };
  /*
   * set the side (left or right) that this object is handling
   */
  void axel_side(enum axel_side axel_side) { _axel_side = axel_side; };
  enum axel_side& axel_side() { return _axel_side; };

  void wheel_diamteter_mm (unsigned int wheel_diameter_mm) { _wheel_diameter_mm = wheel_diameter_mm; };
  unsigned int& wheel_diamteter_mm () { return _wheel_diameter_mm; };

  void rpm(unsigned int rpm);
  const unsigned int& rpm() { return _rpm;};

  void direction(enum motor_direction direction);
  enum motor_direction& direction() {return _direction;}

  void step(unsigned long int steps);
  void keep_stepping(unsigned long int steps);
  unsigned long int& current_steps() { return _current_steps; };
  unsigned long int remaining_steps() { return _target_steps - _current_steps; };

  void stop();
  bool is_stopped() { return !is_running(); };
  bool is_running();

  virtual void run(uint32_t now);
  virtual bool canRun(uint32_t now);
private:
  void init();

  void clock_low();
  void clock_high();

  enum axel_side _axel_side;
  unsigned int _wheel_diameter_mm;
  unsigned int _mode_pin;
  unsigned int _clock_pin;
  unsigned int _cwb_pin;
  unsigned int _enable_pin;
  unsigned int _steps_per_revolution;
  unsigned int _rpm;

  enum motor_direction _direction;

  unsigned long int _last_step_time;
  unsigned long int _next_step_time;
  unsigned long int _target_steps;
  unsigned long int _current_steps;

  unsigned int _milliseconds_to_delay;
  enum hardware_task _next_hardware_task;



};

#endif
