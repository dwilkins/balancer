balancer
========

Arduino code for the balancing robot

This balancing robot is built with stepper motors instead of brush motors, mainly
because I've got a bunch of stepper motors and stepper controller chips lying about


## Hardware:
 * Arduino Mini Pro
 * MP-6050 Accellerometer / Gyro
 * 2x STK672-330 stepper controller chips salvaged from copiers
 * 2x KH42JM2B182 Stepper motors from Japan Servo (also salvaged)
 * 1x 6v battery
 * 1x Project box


## Software:

The general design of the software will be:

 * An axel controls two wheels - left and right
 * An accelrometer reports position information (idk how this works yet)
 * The axel is the point of control for:
   * Turning
   * Balancing
   * Speed and Direction
   * automatic modes (test, follow wall, replay, etc)
 * A command processor that takes commands mainly for the axel in text
   * Serial communication
   * Hopefully over bluetooth serial to an android app

## Current Status
 * Hardware is built
 * stepper control is checked out and working
 * Test infrastructure built
 * Code is broken currently - just committing to make sure it lives past a tragic event


## How to build
 * git clone
 * ./autogen.sh
 * ./configure --host=avr
 * make
 * # balancer.hex is created - ready for avrdude
 * make upload
 * PROFIT!
