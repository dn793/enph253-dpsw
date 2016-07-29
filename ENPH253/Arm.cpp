// 
// NOTE:
//		ARM_SWITCH: true = open , false = closed
//		CLAW Servo: 40 angle is open, 140 angle is closed.

#include "Arm.h"

Arm::Arm() { initialize(); havePassenger = false; }

/*
 * Initializes the position of the claw.
 */
void Arm::initialize()
{
	RCServo2.write(POS_ARM_OPEN);
	delay(DELAY_ARM_INIT);
}

/*
 * Extends the arm until full extension or hit a passenger.
 * Returns true if NO passenger, false if we do have a passenger.
 */
bool Arm::extendPickUp()
{
	bool noPassenger = digitalRead(CLAW_SWITCH);

	motor.speed(ARM_EXTENSION, SPEED_EXTENSION_START);
	while (!digitalRead(ARM_SWITCH)){ /* unclick switch */ }

	delay(DELAY_SWITCH);

	while (digitalRead(ARM_SWITCH) && noPassenger) { noPassenger = close(); }
	stopNow(ARM_EXTENSION, SPEED_EXTENSION_START);

	return noPassenger;
}

/*
 * Extends the arm until full extension and releases the passenger.
 */
void Arm::extendDropOff()
{
	motor.speed(ARM_EXTENSION, SPEED_EXTENSION_START);
	while (!digitalRead(ARM_SWITCH)) { /* unclick switch */ }

	delay(DELAY_SWITCH);

	while (digitalRead(ARM_SWITCH)) { }
	stopNow(ARM_EXTENSION, SPEED_EXTENSION_START);

	open();
}

/*
 * Closes the claw if the claw switch is pushed.
 * Returns false if we have a passenger, true if we do NOT have a passenger.
 */
bool Arm::close()
{
	if (!digitalRead(CLAW_SWITCH)) { RCServo2.write(DELAY_ARM_CLOSE); return false; }
	else { RCServo2.write(POS_ARM_OPEN); return true; }
}

/*
 * Opens the claw.
 */
void Arm::open() { RCServo2.write(POS_ARM_OPEN); delay(DELAY_ARM_OPEN); }

/*
 * Stops the specified motor.
 */
void Arm::stopNow(unsigned char motorVal, unsigned char velocity)
{
	motor.speed(motorVal, velocity * -1);
	delay(DELAY_STOP);
	motor.stop(motorVal);
}
	

/*
 * Retracts the arm.
 */
void Arm::retract()
{
	motor.speed(ARM_EXTENSION, SPEED_RETRACTION_START);
	while (!digitalRead(ARM_SWITCH)) { /* unclick switch */ } 
	
	delay(DELAY_SWITCH);

	while (digitalRead(ARM_SWITCH)){ }
	stopNow(ARM_EXTENSION, SPEED_RETRACTION_START);
}

/*
 * Rotates the arm 90 degrees in the given direction.
 * Direction is 1 for left turn, -1 for right turn.
 * Returns true if on black, false if on white.
 */
bool Arm:: rotateTo90(char dir)
{
	motor.speed(ROTATING_BASE, dir * SPEED_ROTATION_START);
	
	while (digitalRead(BASE_ROTATION_QRD)) { }
	delay(DELAY_QRD_GRAB);
	while (!digitalRead(BASE_ROTATION_QRD)) { }
	delay(DELAY_QRD_GRAB);
	while (digitalRead(BASE_ROTATION_QRD)) { }

	motor.stop(ROTATING_BASE);
	stopNow(ROTATING_BASE, dir * SPEED_ROTATION_START);

	return digitalRead(BASE_ROTATION_QRD);
}

/**
 * Rotates the base back to the home position.
 * The direction parameter should be same direction turned towards the passenger.
 * Assumes on black or white in search area (i.e. turns the opposite of the direction you pass it)
*/
void Arm:: rotateToHome(char dir){
	dir *= -1;

	if (!digitalRead(BASE_ROTATION_QRD))
	{
		motor.speed(ROTATING_BASE, dir * SPEED_ROTATION_START);
		while (!digitalRead(BASE_ROTATION_QRD)) { }
		delay(DELAY_QRD_HOME);
	}
	else { motor.speed(ROTATING_BASE, dir * SPEED_ROTATION_START); }

	while (digitalRead(BASE_ROTATION_QRD)) { }
	delay(DELAY_QRD_HOME);
	while (!digitalRead(BASE_ROTATION_QRD)) { }

	stopNow(ROTATING_BASE, dir * SPEED_ROTATION_START);
}
