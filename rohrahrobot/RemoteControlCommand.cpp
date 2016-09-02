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

#include "RemoteControlCommand.h"
using namespace rohrah;

#define MAX_SPEED 255
#define SPEED_INCREMENT 255 //slower speeds made motor's torque very small. Therefore I did not have any speed increments. Basically, it's always full speed

/**
 * Constructor
 * Initialze the motor speeds to zero and the command to manual mode
 */
RemoteControlCommand::RemoteControlCommand(): leftSpeed(0), rightSpeed(0), key(controlCommand) {}

/**
 * Destructor
 */
RemoteControlCommand::~RemoteControlCommand() {}

/**
 * Increment the forward speed by SPEED_INCREMENT
 * Both motors are set to the same speed.  Max speed possible is 255
 */
void RemoteControlCommand::incrementForward() {
  //make sure that both motors are turning at the same speed
  if (leftSpeed > rightSpeed)
    rightSpeed = leftSpeed;
  else 
    leftSpeed = rightSpeed;
  
  //increment the speed
  leftSpeed += SPEED_INCREMENT;
  rightSpeed += SPEED_INCREMENT;
  
  //max speed is 255
  if (leftSpeed > 255) {
    leftSpeed = 255;
  }
  if (rightSpeed > 255) {
    rightSpeed = 255;
  }
}

/**
 * Increment the backward speed by -SPEED_INCREMENT
 * Both motors are set to the same speed.  Max speed possible is -255
 */
void RemoteControlCommand::incrementBackward() {
  //make sure that both motors are turning at the same speed
  if (leftSpeed < rightSpeed)
    rightSpeed = leftSpeed;
  else 
    leftSpeed = rightSpeed;

  //increment the speed
  leftSpeed -= SPEED_INCREMENT;
  rightSpeed -= SPEED_INCREMENT;

  //max speed is 255
  if (leftSpeed < -255) {
    leftSpeed = -255;
  }
  if (rightSpeed < -255) {
    rightSpeed = -255;
  }
}

/**
 * Increment the left motor's speed by -SPEED_INCREMENT
 * Increment the right motor's speed by SPEED_INCREMENT
 * If both motors are stopped, this makes the motors rotate in opposite direction, causing the robot to spin left
 * However, if both motors are rotating forward, the left motor stops/slows down while the right motor continues to rotate.  This causes the robot to rotate left
 * If both motors are rotating backward, the right motor stops/slows down while the left motor continues to rotate.  
 */
void RemoteControlCommand::incrementLeft() {
  //increment speeds of both motors in opposite directions
  leftSpeed -= SPEED_INCREMENT;
  rightSpeed += SPEED_INCREMENT;

  //max speed is 255
  if (leftSpeed < -255) {
    leftSpeed = -255;
  }
  if (rightSpeed > 255) {
    rightSpeed = 255;
  }
}

/**
 * Increment the right motor's speed by -SPEED_INCREMENT
 * Increment the left motor's speed by SPEED_INCREMENT
 * If both motors are stopped, this makes the motors rotate in opposite direction, causing the robot to spin right
 * However, if both motors are rotating forward, the right motor stops/slows down while the left motor continues to rotate.  This causes the robot to rotate right
 * If both motors are rotating backward, the left motor stops/slows down while the right motor continues to rotate.
 */
void RemoteControlCommand::incrementRight() {
  //increment speeds of both motors in opposite directions
  leftSpeed += SPEED_INCREMENT;
  rightSpeed -= SPEED_INCREMENT;

  //max speed is 255
  if (leftSpeed > 255) {
    leftSpeed = 255;
  }
  if (rightSpeed < -255) {
    rightSpeed = -255;
  }
}

/**
 * Stop the motors
 */
void RemoteControlCommand::stop(){
  leftSpeed = 0;
  rightSpeed = 0;
}

/**
 * Set left motor's speed to a specified value
 */
void RemoteControlCommand::setLeftSpeed(int speed) {
  leftSpeed = speed;
}

/**
 * Get the left motor's speed
 */
int RemoteControlCommand::getLeftSpeed() {
  return leftSpeed;
}

/**
 * Set right motor's speed to a specified value
 */
void RemoteControlCommand::setRightSpeed(int speed) {
  rightSpeed = speed;
}

/**
 * Get the right motor's speed
 */
int RemoteControlCommand::getRightSpeed() {
  return rightSpeed;
}

/**
 * Set the command's key type to either 'auto' 'manual' or 'move' type
 */
void RemoteControlCommand::setKeyType(key_t type) {
  key = type;
}

/**
 * Return the command's key type
 */
RemoteControlCommand::key_t RemoteControlCommand::getKeyType() {
  return key;
}

