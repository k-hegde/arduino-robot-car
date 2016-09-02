//
//  Robot Car using Arduino Uno
//
//  Author: Kiran Hegde
//  http://www.rohrah.com/
//  Copyright (c) 2016 
//
//  My code utilizes ideas and code from http://blog.miguelgrinberg.com/
//  and therefore I have included the relevant license below
//
//
// Michelino
// Robot Vehicle firmware for the Arduino platform
// Copyright (c) 2013 by Miguel Grinberg
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is furnished
// to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
// AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "Motor.h"
using namespace rohrah;

/**
 * Constructor 
 * Initializes the motor member variable with the number and sets the current speed to zero
 * Uses the Adafruit motor shield and associated library 
 */
Motor::Motor(int number): motor(number), currentSpeed(0) {
}

/**
 * Destructor
 */
Motor::~Motor() {
}

/**
 * Sets speed of the motor
 * Range of values from -255 to +255.  
 * Positive values signifies forward direction
 * Negative values signifies backward direction
 * Zero means stop
 */
void Motor::setSpeed(int speed) {
    currentSpeed = speed;
    if(speed >0) { //forward
      motor.setSpeed(speed);
      motor.run(FORWARD);
    }
    else if (speed <0) { //backward
      motor.setSpeed(-speed);
      motor.run(BACKWARD);
    }
    else { //stop
      motor.setSpeed(0);
      motor.run(RELEASE);
    }
}

/**
 * Get the current motor speed
 */
int Motor::getSpeed() const {
    return currentSpeed;
}
  

