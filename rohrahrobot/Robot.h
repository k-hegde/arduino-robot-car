//
//  Robot Car using Arduino Uno
//
//  Author: Kiran Hegde
//  http://www.rohrah.com/
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

#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <SoftwareSerial.h>
#include "Motor.h"
#include "DistanceSensor.h"
#include "RemoteControl.h"
#include "MovingAverage.h"


namespace rohrah {

  class Robot {
    public:
      Robot(SoftwareSerial *ss);
      ~Robot();
      void run();
      void initialize();

   protected:
      void move();
      void stop();
      void turn(unsigned long currentTime);
      bool doneTurning(unsigned long currentTime, unsigned int distance);
      bool obstacleAhead(unsigned int distance);
      void controlByRemote();
      void switchToAutoControl();
      bool doneRunning(unsigned long currentTime);
      void processCommand(RemoteControlCommand &command);
      
      bool isMoving() { return (currentState == stateMoving); }
      bool isStopped() { return (currentState == stateStopped); }
      bool isTurning() { return (currentState == stateTurning); }
      bool isRemoteControlled() { return (currentState == stateRemote); }
      
      void blink(unsigned long currentTime);
          
    private:
      Motor leftMotor;
      Motor rightMotor;
      DistanceSensor distanceSensor;
      MovingAverage averageDistance;
      RemoteControl remoteControl;
      enum state_t {stateStopped, stateMoving, stateTurning, stateRemote };
      state_t currentState;
      unsigned long endStateTime;
      unsigned long endBlinkTime;
      bool isLedOn;
      unsigned long endTime;
      SoftwareSerial *btSerial;
  };
 
}

#endif
