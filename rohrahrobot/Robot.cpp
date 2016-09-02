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
#include "DistanceSensor.h"
#include "RemoteControl.h"
#include "Robot.h"
#include "Logger.h"

using namespace rohrah;

// constants
#define MIN_DIST_TO_OBSTACLE 10 //10cm     
#define MAX_DISTANCE_TO_TRACK (MIN_DIST_TO_OBSTACLE * 60) //600cm  
#define MOVING_AVG_WINDOW_SIZE 10 

// run time in seconds when in auto mode
#define RUN_TIME 30 

// blink time in seconds
#define BLINK_INTERVAL 2

//pins on motor shield
#define LEFT_MOTOR_NUMBER 1
#define RIGHT_MOTOR_NUMBER 4

//pins on arduino
#define RANDOM_ANALOG_PIN 5 //unconnected pin for random input 
#define ECHO_PIN 14 //pin A0
#define TRIGGER_PIN 15 //pin A1
#define LED_PIN 13 //for the blinking LED

/**
 * Constructor.  Make sure that we initialize all the member variables
 */
Robot::Robot(SoftwareSerial *ss) : leftMotor(LEFT_MOTOR_NUMBER), rightMotor(RIGHT_MOTOR_NUMBER),
                 distanceSensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE_TO_TRACK),
                 averageDistance(MIN_DIST_TO_OBSTACLE * 10, MOVING_AVG_WINDOW_SIZE), remoteControl(ss), isLedOn(false), endBlinkTime(0) {
  initialize();
}

/**
 * Destructor.  Nothing to do.
 */
Robot::~Robot(){
  
}

/**
 * Initialize the robot.  This needs to run only once
 */
void Robot::initialize() {
  randomSeed(analogRead(RANDOM_ANALOG_PIN)); //for random number generation
  leftMotor.setSpeed(0);
  rightMotor.setSpeed(0);
  controlByRemote();
  pinMode(13, OUTPUT); //LED
}

/**
 * Just set the state of the robot to remote
 */
void Robot::controlByRemote() {
  currentState = stateRemote;
}

/**
 * Start moving the robot forward and set state accordingly
 */
void Robot::move() {
  leftMotor.setSpeed(255); //full speed ahead
  rightMotor.setSpeed(255);
  currentState = stateMoving;
}

/**
 * Stop the robot and set state accordingly
 */
void Robot::stop() {
  leftMotor.setSpeed(0);
  rightMotor.setSpeed(0);
  currentState = stateStopped;
}

/**
 * Spins the robot in place by moving both motors in opposite directions
 * turning continues for between 0.5 and 1 second chosen at random
 */
void Robot::turn(unsigned long currentTime) {
  if (random(2) == 0) { //turn left
    rightMotor.setSpeed(255);
    leftMotor.setSpeed(-255);
  }
  else { //turn right
    rightMotor.setSpeed(-255);
    leftMotor.setSpeed(255);
  }
  currentState = stateTurning;
  endStateTime = currentTime + random(500, 1000);  
}

/**
 * Switch to auto control.  endTime for autocontrol is set to 
 * the 30 seconds from now
 */
void Robot::switchToAutoControl() {
  //set both motors to full speed ahead
  leftMotor.setSpeed(255);
  rightMotor.setSpeed(255);
  currentState = stateMoving;
  endTime = millis() + RUN_TIME*1000;
}

/**
 * If moving average distance of robot from an obstacle is less than 10cm return true
 * otherwise return false
 */
bool Robot::obstacleAhead(unsigned int distance) {
  return (distance <= MIN_DIST_TO_OBSTACLE);
}

/**
 * If the robot has done turning for 0.5 to 1 seconds (decided at random), 
 * check to make sure that the robot is not going to crash into an obstacle.
 * If there is an obstacle ahead continue to turn
 */
bool Robot::doneTurning(unsigned long currentTime, unsigned int distance) {
  if (currentTime >= endStateTime)
    return (distance > MIN_DIST_TO_OBSTACLE);
  return false;
}

/**
 * Process the command receieved
 */
void Robot::processCommand(RemoteControlCommand &command) {
  if (command.getKeyType() == RemoteControlCommand::controlCommand) {
    controlByRemote();
    //Initialize speed to current speed
    command.setLeftSpeed(leftMotor.getSpeed());
    command.setRightSpeed(rightMotor.getSpeed());
  }
  else if (command.getKeyType() == RemoteControlCommand::autoCommand) {
    switchToAutoControl();
  }
  else {
    //do nothing
  }
}

/**
 * Check if done running in automode (i.e. robot has been in automode for 30 seconds or more)
 */
bool Robot::doneRunning(unsigned long currentTime) {
  return (currentTime >= endTime);
}

/**
 * This method runs during every loop() of the Arduino sketch
 */
void Robot::run() {
  unsigned long currentTime = millis();
  int distance = averageDistance.add(distanceSensor.getDistance());
  RemoteControlCommand command;
  bool haveCommand = remoteControl.receiveAndParseCommand();
 
  if (haveCommand) {
    command = remoteControl.getCommand();
    processCommand(command);
    //Logger outputs to serial terminal only if LOGGING is defined in rohrahrobot
    Logger::log((char *)"currentState: %d, currentTime: %d, distance: %d, haveCommand: %d, keyType: %d\n", 
      currentState, currentTime, distanceSensor.getDistance(), command.getKeyType());
  }
  
  if(isRemoteControlled()) { //Manual or Remote control mode
    if (haveCommand) { //only if a button is pressed
      //Logger outputs to serial terminal only if LOGGING is defined in rohrahrobot
      Logger::log((char *)"Motor Command: %d, leftSpeed: %d, rightSpeed: %d\n", command.getKeyType(), command.getLeftSpeed(), command.getRightSpeed());        
      leftMotor.setSpeed(command.getLeftSpeed());
      rightMotor.setSpeed(command.getRightSpeed());
    }
  }
  else { //Auto mode
    if (isStopped())
      return;    
    if (doneRunning(currentTime)) {
      stop();
    }
    else if (isMoving()) {
      if (obstacleAhead(distance))
        turn(currentTime);
    }
    else if (isTurning()) {
      if (doneTurning(currentTime, distance))
        move();
    }
  }
  blink(currentTime);
}

/**
 * A function to just make an LED blink at regular intervals
 */
void Robot::blink(unsigned long currentTime) {
  if (currentTime > endBlinkTime) {
    endBlinkTime = currentTime + BLINK_INTERVAL*1000;
    if (isLedOn) {
      digitalWrite(LED_PIN, LOW);
      isLedOn = false;
    }
    else {
      digitalWrite(LED_PIN, HIGH);
      isLedOn = true;
    }
  }
}


