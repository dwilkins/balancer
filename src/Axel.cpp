/* Axel.cpp
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

#include <Arduino.h>
#include "BalanceWheel.hpp"
#include "Axel.hpp"



Axel::Axel() : right_wheel(R_STK_MODE_PIN,R_STK_CLOCK_PIN, R_STK_CWB_PIN, R_STK_ENABLE_PIN),
               left_wheel(L_STK_MODE_PIN,L_STK_CLOCK_PIN, L_STK_CWB_PIN, L_STK_ENABLE_PIN) {

}

/*
 * Maybe Axel should respond somehow with a list of child tasks
 */


bool Axel::canRun(uint32_t now) {
  bool wheels = right_wheel.canRun(now) || left_wheel.canRun(now);
  /* prolly add some axel related stuff now */
  return wheels;
}


void Axel::run(uint32_t now) {
  if(right_wheel.canRun(now)) {
    right_wheel.run(now);
  }
  if(left_wheel.canRun(now)) {
    left_wheel.run(now);
  }
  /* prolly add some axel related stuff now */
}


