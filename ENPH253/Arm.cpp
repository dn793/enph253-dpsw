#include "Arm.h"

bool havePassenger = digitalRead(CLAW_SWITCH);
int passengerState = detectPassenger();
bool doPID = false;

void pickupPassenger()
{
	if (passengerState != 0 && havePassenger)
	{
		//rotate arm in passengerState direction to pre-set position to start search
		//extend arm to start
		//Lower arm to horizontal to start
		startArm(passengerState);

		//begin rotation until arm centered at PID start
		//when centered begin PID    // if max return home and keep going/repeat???
		doPID = rotateBasePID(passengerState);

		//Do PID until hit threshold in center or passenger touch sensor
		//close claw (servo turn x amount)
		//retract
		if (doPID) { }

		//go to home position
		moveArmHome(passengerState, havePassenger);
	}
}

int detectPassenger()
{
	int topLeft = analogRead(TOPLEFT_PASS_DETECT);
	int bottomLeft = analogRead(BOTTOMLEFT_PASS_DETECT);
	int topRight = analogRead(TOPRIGHT_PASS_DETECT);
	int bottomRight = analogRead(TOPLEFT_PASS_DETECT);

	if ((topLeft && bottomLeft) >= PASSENGER_DETECTED_THRESHOLD) { return -1; }
	else if ((topRight && bottomRight) >= PASSENGER_DETECTED_THRESHOLD) { return 1; }
	else { return 0; }
}

void startArm(int state)
{
	motor.speed(ROTATING_BASE, ARM_START_ROT_SPEED * state);

	while (digitalRead(BASE_ROTATION_QRD) == false) { }
	while (digitalRead(BASE_ROTATION_QRD) == true) { }

	// for testing. in actual code probably better to got straight into pid
	stopArmNow(ROTATING_BASE, ARM_START_ROT_SPEED * state * -1);

	// Tilts arm from up to down position
	// Turn tilt motor on should go down
	// turn tilt motor on
	while (digitalRead(TILT_SWITCH) == true) { }
	while (digitalRead(TILT_SWITCH) == false) { }
}

bool rotateBasePID(int state)
{
	bool rightArray = digitalRead(RIGHT_SENSOR_ARRAY);
	bool leftArray = digitalRead(LEFT_SENSOR_ARRAY);
	bool baseQRD = digitalRead(BASE_ROTATION_QRD);
	bool found = false;

	motor.speed(ROTATING_BASE, ARM_START_ROT_SPEED * state);

	//look for general center or max turn distance // on black
	while (!baseQRD)
	{
		rightArray = digitalRead(RIGHT_SENSOR_ARRAY);
		leftArray = digitalRead(LEFT_SENSOR_ARRAY);
		baseQRD = digitalRead(BASE_ROTATION_QRD);

		if (rightArray && leftArray)
		{
			stopArmNow(ROTATING_BASE, ARM_START_ROT_SPEED * state * -1);
			return true;
		}
	}

	//hit the middle line on rotation gear
	while (baseQRD)
	{
		rightArray = digitalRead(RIGHT_SENSOR_ARRAY);
		leftArray = digitalRead(LEFT_SENSOR_ARRAY);
		baseQRD = digitalRead(BASE_ROTATION_QRD);

		if (rightArray && leftArray)
		{
			stopArmNow(ROTATING_BASE, ARM_START_ROT_SPEED * state * -1);
			return true;
		}
	}

	stopArmNow(ROTATING_BASE, ARM_START_ROT_SPEED * state * -1);
	motor.speed(ROTATING_BASE, ARM_START_ROT_SPEED * state * -1);

	// hit max distance on roation gear //on black again
	//head opposite way
	
	//get off black at max dist
	while (!baseQRD) { baseQRD = digitalRead(BASE_ROTATION_QRD); }

	while (baseQRD)
	{
		rightArray = digitalRead(RIGHT_SENSOR_ARRAY);
		leftArray = digitalRead(LEFT_SENSOR_ARRAY);
		baseQRD = digitalRead(BASE_ROTATION_QRD);

		if (rightArray && leftArray) {
			stopArmNow(ROTATING_BASE, ARM_START_ROT_SPEED * state * -1);
			return true;
		}
	}

	while (!baseQRD) {
		rightArray = digitalRead(RIGHT_SENSOR_ARRAY);
		leftArray = digitalRead(LEFT_SENSOR_ARRAY);
		baseQRD = digitalRead(BASE_ROTATION_QRD);

		if (rightArray && leftArray) {
			stopArmNow(ROTATING_BASE, ARM_START_ROT_SPEED * state * -1);
			return true;
		}
	}
	//scanned back and forth and didnt find somewhere to start PID so return false
	stopArmNow(ROTATING_BASE, ARM_START_ROT_SPEED * state);

	return false;
}

// TODO: change time stuff to switches to detect max and min extension
bool armPID(int state)
{
	int centerArray = analogRead(CENTER_SENSOR_ARRAY);
	bool rightArray = digitalRead(RIGHT_SENSOR_ARRAY);
	bool leftArray = digitalRead(LEFT_SENSOR_ARRAY);
	long extensionTimeInitial = millis();
	long extensionTimeFinal = 2147483647;
	bool isClosed = false;

	while (!digitalRead(CLAW_SWITCH) &&
		(extensionTimeFinal - extensionTimeInitial) <= FULL_EXTENSION_TIME &&
		analogRead(CENTER_SENSOR_ARRAY) <= PLATFORM_THRESHOLD)
	{
		// put arm PID here

		extensionTimeFinal = millis();
	}

	stopArmNow(ROTATING_BASE, ARM_START_ROT_SPEED * state * -1);

	if (digitalRead(CLAW_SWITCH)) { isClosed = true; }

	moveArm(BACK);

	return isClosed;
}

void moveArm(int direction)
{
	motor.speed(ARM_EXTENSION, ARM_START_EXT_SPEED * direction);
	while (digitalRead(ARM_SWITCH) == false) {	}
	stopArmNow(ARM_EXTENSION, ARM_START_EXT_SPEED * direction * -1);
}

void moveArmHome(int state, bool havePassenger)
{
	//Tilts arm from down to up position

	//Turn tilt motor on should go up

	//turn tilt motor on
	while (digitalRead(TILT_SWITCH)) { }
	while (!digitalRead(TILT_SWITCH)) {	}

	//turn off tilt motor

	motor.speed(ROTATING_BASE, ARM_START_ROT_SPEED * state * -1);

	while (digitalRead(BASE_ROTATION_QRD)) { }

	motor.stop(ROTATING_BASE);

	if (!havePassenger) { RCServo0.write(0); }
}

void stopArmNow(int motorVal, int velocity)
{
	motor.speed(motorVal, velocity);
	delay(100);
	motor.stop(motorVal);
}