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

#include "MovingAverage.h"
using namespace rohrah;

/**
 * Constructor
 * Defines a sliding window with all values in the window initialized to defaultVal
 * The window's size is equal to length
 * Average of the values within this sliding window is calculated
 */
MovingAverage::MovingAverage(int defaultVal, int length): size(length), index(0), sum(0) {
  buffer = new int[size];
  for (int i=0; i<size; i++) {
    buffer[i] = defaultVal;
    sum += buffer[i];
  }
}

/**
 * Destructor
 */
MovingAverage::~MovingAverage(){
  delete buffer;
}

/**
 * Adds newValue to the sliding window and removes the oldest value
 * Returns the newly calculated moving average
 */
int MovingAverage::add(int newValue) {  
    sum = sum - buffer[index] + newValue;
    buffer[index++] = newValue;
    if (index >= size) {
      index = 0;
    }
    return (sum / size);
}
