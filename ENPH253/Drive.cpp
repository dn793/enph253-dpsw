#include "Drive.h"

unsigned char rightLine;
unsigned char leftLine;
unsigned char rightNode;
unsigned char leftNode;

extern "C" Drive * createDrive()
{
	Drive *drive;
	drive = (Drive *)malloc(sizeof(Drive));
	
	drive->kp = 30;
	drive->kd = 10;
	drive->error = 0;
	drive->prevError = 0;
	drive->lastError = 0;
	drive->q = 1;
	drive->m = 0;

	return drive;
}

void lineFollow(Drive *drive)
{
	rightNode = digitalRead(RIGHT_NODE);
	rightLine = digitalRead(FRONT_RIGHT_LINE);
	leftLine = digitalRead(FRONT_LEFT_LINE);
	leftNode = digitalRead(LEFT_NODE);

	if (leftLine && rightLine) { drive->error = 0; }
	else if (leftLine && !(rightLine)) { drive->error = -1; }
	else if (!(leftLine) && rightLine) { drive->error = +1; }
	else if (!(leftLine) && !(rightLine))
	{
		if (drive->lastError > 0) { drive->error = 5; }
		else { drive->error = -5; }
	}
	if (!(drive->error == drive->lastError))
	{
		drive->prevError = drive->lastError;
		drive->q = drive->m;
		drive->m = 1;
	}

	drive->prop = drive->kp * drive->error;
	drive->der = drive->kd * (drive->error - drive->prevError) / (drive->q + drive->m);
	drive->corr = drive->prop + drive->der;

	++drive->m;

	if (200 - drive->corr < -255) { drive->velocity = -255; }
	else if (200 + drive->corr > 255) { drive->velocity = 255; }

	if (digitalRead(EDGE)) { stopNow(); }
	else
	{
		motor.speed(RIGHT_WHEEL, drive->velocity - drive->corr);
		motor.speed(LEFT_WHEEL, drive->velocity + drive->corr);
	}
	
	drive->lastError = drive->error;
}

void driveForward(unsigned char speed)
{
	motor.speed(RIGHT_WHEEL, speed);
	motor.speed(LEFT_WHEEL, speed);
}

void reverse(unsigned char speed)
{
	motor.speed(RIGHT_WHEEL, -1 * speed);
	motor.speed(LEFT_WHEEL, -1 * speed);
}

void turnLeft(Drive *drive)
{
	motor.speed(RIGHT_WHEEL, MAX_SPEED);
	motor.speed(LEFT_WHEEL, 0);
	delay(DELAY_TURN);
	if (digitalRead(FRONT_RIGHT_LINE)) { drive->lastError = 1; }
	else { turnLeft(drive); }
}

void turnRight(Drive *drive)
{
	motor.speed(RIGHT_WHEEL, 0);
	motor.speed(LEFT_WHEEL, MAX_SPEED);
	delay(DELAY_TURN);
	if (digitalRead(FRONT_LEFT_LINE)) { drive->lastError = -1; }
	else { turnRight(drive); }
}

void hardLeft(Drive *drive)
{
	motor.speed(RIGHT_WHEEL, MAX_SPEED);
	motor.speed(LEFT_WHEEL, -MAX_SPEED);
	delay(DELAY_TURN);
	if (digitalRead(FRONT_RIGHT_LINE)) { drive->lastError = 1; }
	else { hardLeft(drive); }
}

void hardRight(Drive *drive)
{
	motor.speed(RIGHT_WHEEL, -MAX_SPEED);
	motor.speed(LEFT_WHEEL, MAX_SPEED);
	delay(DELAY_TURN);
	if (digitalRead(FRONT_LEFT_LINE)) { drive->lastError = -1; }
	else { hardRight(drive); }
}

void turnAroundLeft(Drive * drive) {
	motor.speed(RIGHT_WHEEL, MAX_SPEED);
	motor.speed(LEFT_WHEEL, -MAX_SPEED);
	delay(DELAY_180);
	if (digitalRead(FRONT_RIGHT_LINE)) { drive->lastError = 1; }
	else { hardLeft(drive); }
}

void turnAroundRight(Drive * drive) {
	motor.speed(RIGHT_WHEEL, -MAX_SPEED);
	motor.speed(LEFT_WHEEL, MAX_SPEED);
	delay(DELAY_180);
	if (digitalRead(FRONT_RIGHT_LINE)) { drive->lastError = 1; }
	else { hardRight(drive); }
}

void stop()
{
	motor.stop(RIGHT_WHEEL);
	motor.stop(LEFT_WHEEL);
}

void stopNow()
{
	motor.speed(LEFT_WHEEL, -MAX_SPEED);
	motor.speed(RIGHT_WHEEL, -MAX_SPEED);
	delay(DELAY_STOP);
	motor.stop(LEFT_WHEEL);
	motor.stop(RIGHT_WHEEL);
}

extern "C" void setKP(Drive *drive) { drive->kp = knob(KNOB) / 4; }

extern "C" void setKD(Drive *drive) { drive->kd = knob(KNOB) / 4; }

extern "C" unsigned char getKP(Drive *drive) { return drive->kp; }

extern "C" unsigned char getKD(Drive *drive) { return drive->kd; }