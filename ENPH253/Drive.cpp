// 
// Implements Drive.h
// The Drive class specifies and implements the driving movements of the robot
// 

#include "Arduino.h"
#include "Drive.h"
#include "Pins.h"

Drive::Drive(){
	kp = 30;
	kd = 10;
	error = 0;
	prevError = 0;
	lastError = 0;
	q = 1;
	m = 0;
}

/**
Drives the robot forward, along tape
*/
void Drive:: lineFollow(){

	rightNode = digitalRead(RIGHT_NODE);
	rightLine = digitalRead(FRONT_RIGHT_LINE);
	leftLine = digitalRead(FRONT_LEFT_LINE);
	leftNode = digitalRead(LEFT_NODE);
	edge = digitalRead(EDGE);

	//Read sensors and determine correction
	if (leftLine && rightLine) error = 0;
	if (leftLine && !(rightLine)) error = -1;
	if (!(leftLine) && rightLine) error = +1;
	if (!(leftLine) && !(rightLine))
	{
		if (lastError > 0) error = 5;
		if (lastError <= 0) error = -5;
	}
	if (!(error == lastError))
	{
		prevError = lastError;
		q = m;
		m = 1;
	}

	prop = kp * error;
	der = (int)((float)kd *(float)(error - prevError) / (float)(q + m));
	corr = prop + der;

	m = m + 1;

	velocity = 200;

	if (velocity - corr < -255){
		velocity = -255;
	}
	if (velocity + corr> 255){
		velocity = 255;
	}

	if (edge){
		stopNow();
	}
	else{
		motor.speed(RIGHT_WHEEL, velocity - corr);
		motor.speed(LEFT_WHEEL, velocity + corr);
	}

	lastError = error;
}

/**
 Drive the robot straight forward; does NOT line follow
  @param speed: speed of robot is between 0 and 255
 */
void Drive::driveForward(int speed){
	motor.speed(RIGHT_WHEEL, speed);
	motor.speed(LEFT_WHEEL, speed);
}

/**
Drive the robot straight backwards; does NOT line follow
 @param speed: speed of robot is between 0 and -255
*/
void Drive::reverse(int speed){
	motor.speed(RIGHT_WHEEL, speed);
	motor.speed(LEFT_WHEEL, speed);
}

/**
Turns the robot to the left, robot turns about left wheel
*/
void Drive::turnLeft(){
	motor.speed(RIGHT_WHEEL, MAX_SPEED);
	motor.speed(LEFT_WHEEL, 0);
	delay(200); //delay ensures that robot has turned enough so that the sensor will return data from the porper line
	if (digitalRead(FRONT_RIGHT_LINE)){
		lastError = 1;
	}
	else{
		turnLeft();
	}
}

/**
Turns the robot to the right, robot turns about right wheel
*/
void Drive::turnRight(){
	motor.speed(RIGHT_WHEEL, 0);
	motor.speed(LEFT_WHEEL, MAX_SPEED);
	delay(200); //delay ensures that robot has turned enough so that the sensor will return data from the porper line
	if (digitalRead(FRONT_LEFT_LINE)){
		lastError = -1;
	}
	else{
		turnRight();
	}
}

/*
Makes a hard right, robot turns about centre axis
*/
void Drive::hardLeft(){
	motor.speed(RIGHT_WHEEL, MAX_SPEED);
	motor.speed(LEFT_WHEEL, -MAX_SPEED);
	delay(200); //delay ensures that robot has turned enough so that the sensor will return data from the porper line
	if (digitalRead(FRONT_RIGHT_LINE)){
		lastError = 1;
	}
	else{
		hardLeft();
	}
}

/*
Makes a hard right, robot turns about centre axis
*/
void Drive::hardRight(){
	motor.speed(RIGHT_WHEEL, -MAX_SPEED);
	motor.speed(LEFT_WHEEL, MAX_SPEED);
	delay(200); //delay ensures that robot has turned enough so that the sensor will return data from the porper line
	if (digitalRead(FRONT_LEFT_LINE)){
		lastError = -1;
	}
	else{
		hardRight();
	}
}

/*
Makes the robot do a 180 degree turn (turns to the left, about its centre axis)
*/
void Drive::turnAround(){
	motor.speed(RIGHT_WHEEL, MAX_SPEED);
	motor.speed(LEFT_WHEEL, -MAX_SPEED);
	delay(400); //delay ensures that robot has turned enough so that the sensor will return data from the porper line
	if (digitalRead(FRONT_RIGHT_LINE)){
		lastError = 1;
	}
	else{
		hardLeft();
	}
}

/*
Stops the robot
*/
void Drive::stop(){
	motor.stop(RIGHT_WHEEL);
	motor.stop(LEFT_WHEEL);
}

/*
Stops the robot immediately
*/
void Drive:: stopNow(){
	motor.speed(LEFT_WHEEL, -MAX_SPEED);
	motor.speed(RIGHT_WHEEL, -MAX_SPEED);
	delay(50);
	motor.stop(LEFT_WHEEL);
	motor.stop(RIGHT_WHEEL);
}

/**
Set the proportional constant
*/
void Drive::setKP(){
	kp = knob(KNOB)/3;
}

/**
Set the derivative constant
*/
void Drive::setKD(){
	kd = knob(KNOB)/3;
}

/**
@return the proportional constant
*/
int Drive::getKP(){
	int copy = kp;
	return copy;
}

/**
@return the derivative constant
*/
int Drive::getKD(){
	int copy = kd;
	return copy;
}