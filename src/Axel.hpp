/* Axel.hpp
 *
 * Class for handling two steppers acting as an Axel
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
 **
 */
#ifndef AXEL_HPP
#define AXEL_HPP

#include <Arduino.h>
#include "BalanceWheel.hpp"


class Axel : public Task {
  public:
  Axel();

  enum axel_direction {FORWARD,REVERSE,IN_PLACE};

  virtual void run(uint32_t now);
  virtual bool canRun(uint32_t now);

  bool is_running(){return (right_wheel.is_running() || left_wheel.is_running());}




private:
  enum axel_direction _direction;
  BalanceWheel right_wheel;
  BalanceWheel left_wheel;


// Getters and Setters
  public:
  int direction(enum axel_direction direction) { _direction = direction; return 0; };
  enum axel_direction& direction() { return _direction; };

};

#endif
