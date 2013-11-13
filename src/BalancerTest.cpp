/* BalancerTest.cpp
 *
 * Tests for the Balancer
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

#include "balancer.hpp"
#include "BalancerTest.hpp"



bool BalancerTest::canRun(uint32_t now) {
  return true;
}

void BalancerTest::run(uint32_t now) {

}


enum BalancerTest::test_status BalancerTest::test_forward(uint32_t now) {
  static enum test_status my_status = NONE;
  switch(my_status) {
  case NONE:
  case STARTUP:
  case RUNNING:
  case TEARDOWN:
  case FINISHED:
  case SUCCESS:
  case FAILED:
    return my_status;
  }



  return RUNNING;
}


enum BalancerTest::test_status BalancerTest::test_reverse(uint32_t now) {
  return RUNNING;
}
