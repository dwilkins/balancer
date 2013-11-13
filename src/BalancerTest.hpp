/* BalanceTest.hpp
 *
 * Externs and whatnot for the balancer project
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

#ifndef BALANCERTEST_HPP
#define BALANCERTEST_HPP

#include "Task.hpp"


class BalancerTest: public Task {
  public:
  BalancerTest(unsigned long int delay_between_tests,
               unsigned long int delay_between_suites) :
    tests({
      {.fn = &BalancerTest::test_forward, .wait = 2000,.timeout = 2000},
      {.fn = &BalancerTest::test_reverse, .wait = 2000,.timeout = 2000},
      {.fn = NULL, .wait = 0,.timeout = 0}
  })
{
    _delay_between_tests = delay_between_tests;
    _delay_between_suites = delay_between_suites;
    _current_test_start = _current_test = _current_test_time = 0;
  }

  enum test_status { NONE,STARTUP,RUNNING,TEARDOWN,FINISHED,SUCCESS,FAILED };

  virtual void run(uint32_t now);
  virtual bool canRun(uint32_t now);

  enum BalancerTest::test_status test_forward(uint32_t now);
  enum BalancerTest::test_status test_reverse(uint32_t now);

  private:

  unsigned long int _delay_between_tests;
  unsigned long int _delay_between_suites;

  struct test_steps {
    enum BalancerTest::test_status (BalancerTest::*fn)(uint32_t);
    unsigned long int wait;
    unsigned long int timeout;
  };


  struct test_steps tests[3];


  int _current_test;
  unsigned long int _current_test_start;
  unsigned long int _current_test_time;

  unsigned long int _next_test_start;


  /*
   * Getters and Setters
   */
  public:
  void delay_between_tests(unsigned long int delay) {_delay_between_tests = delay; };
  unsigned long int& delay_between_tests() {return _delay_between_tests;}


  void delay_between_suites(unsigned long int delay) {_delay_between_suites = delay; };
  unsigned long int& delay_between_suites() {return _delay_between_suites;}

};

#endif
