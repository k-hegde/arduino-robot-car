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

#include "RemoteControl.h"
using namespace rohrah;

/**
 * Constructor 
 * Initialze the Bluetooth Serial object
 */
RemoteControl::RemoteControl(SoftwareSerial *ss): btSerial(ss) {
}

/**
 * Recieve command from the transmitter and parse the command
 * The protocol is such that each command consists of single character
 * If 'a' is received, the command is to move left
 * If 'd' is received, the command is to move right
 * If 'w' is received, the command is to move forward
 * If 'x' is received, the command is to move backward
 * If 's' is received, the command is to stop
 * If 'A' is received, the command is to set the robot to Auto mode
 * If 'R' is received, the command is to set the robot to Manual mode (or take control)
 * 
 * Returns true if a character is received on the bluetooth terminal, false otherwise
 */
bool RemoteControl::receiveAndParseCommand() {
  if (btSerial->available() <= 0) 
    return false;
      
  //read data from Bluetooth
  char ch = btSerial->read();
  
  switch (ch) {
    case 'a': //left
      command.setKeyType(RemoteControlCommand::moveCommand);
      command.incrementLeft();
      break;
    case 'd': //right
      command.setKeyType(RemoteControlCommand::moveCommand);
      command.incrementRight();
      break;
    case 'w': //forward
      command.setKeyType(RemoteControlCommand::moveCommand);
      command.incrementForward();
      break;
    case 'x': //backward
      command.setKeyType(RemoteControlCommand::moveCommand);
      command.incrementBackward();
      break;
    case 's': //stop
      command.setKeyType(RemoteControlCommand::moveCommand);
      command.stop();
      break;
    case 'A': //auto
      command.setKeyType(RemoteControlCommand::autoCommand);
      break;
    case 'R': //take control
      command.setKeyType(RemoteControlCommand::controlCommand);
      break;
    default:
      break;
  }
  return true;
}

/**
 * Return the current command received and parsed
 */
RemoteControlCommand RemoteControl::getCommand() {
  return command;
}

