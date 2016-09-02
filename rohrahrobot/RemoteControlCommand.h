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

#ifndef _REMOTE_CONTROL_COMMAND_H_
#define _REMOTE_CONTROL_COMMAND_H_

namespace rohrah {

  class RemoteControlCommand {
    public:
      RemoteControlCommand();
      ~RemoteControlCommand();
      enum key_t {controlCommand, autoCommand, moveCommand}; 
      void incrementForward();
      void incrementBackward();
      void incrementLeft();
      void incrementRight();
      void stop();
      void setLeftSpeed(int speed);
      void setRightSpeed(int speed);
      int getLeftSpeed();
      int getRightSpeed();
      key_t getKeyType();
      void setKeyType(key_t type);
      
    private:
      int leftSpeed;
      int rightSpeed;
      key_t key;       
  };
}

#endif
