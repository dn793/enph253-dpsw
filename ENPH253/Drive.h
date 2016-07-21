#ifndef drive_h
#define drive_h

#include <phys253.h>
#include "Pins.h"

#define MAX_SPEED 255
#define DELAY_TURN 200
#define DELAY_180 400
#define DELAY_STOP 50

typedef struct Drive
{
	double kp;
	double kd;
	double der;
	double prop;
	double corr;
	double error;
	double prevError;
	double lastError;
	double velocity;
	double q;
	double m;
} Drive;

/*
 * Create Drive object and set initial variables.
 */
extern "C" Drive * createDrive();

/*
 * Drives the robot forward, along tape.
 */
void lineFollow(Drive *drive);

/*
 * Drive the robot straight forward; does NOT line follow.
 * @param speed: speed of robot is between 0 and 255
 */
void driveForward(unsigned char speed);

/*
 * Drive the robot straight backwards; does NOT line follow.
 * @param speed: speed of robot is between 0 and 255
 */
void reverse(unsigned char speed);

/*
 * Turns the robot to the left, robot turns about left wheel.
 */
void turnLeft(Drive *drive);

/*
 * Turns the robot to the right, robot turns about right wheel.
 */
void turnRight(Drive *drive);

/*
 * Makes a hard left, robot turns about centre axis.
 */
void hardLeft(Drive *drive);

/*
 * Makes a hard right, robot turns about centre axis.
 */
void hardRight(Drive *drive);

/*
 * Makes the robot do a 180 degree turn (turns to the left, about its centre axis).
 */
void turnAroundLeft(Drive * drive);

/*
* Makes the robot do a 180 degree turn (turns to the right, about its centre axis).
*/
void turnAroundRight(Drive * drive);

/*
 * Stops the robot.
 */
void stop();

/*
 * Stops the robot immediately.
 */
void stopNow();

/*
 * Set the proportional constant.
 */
extern "C" void setKP(Drive *drive);

/*
 * Set the derivative constant.
 */
extern "C" void setKD(Drive *drive);

/*
 * Returns the proportional constant.
 */
extern "C" unsigned char getKP(Drive *drive);

/*
 * Returns the derivative constant.
 */
extern "C" unsigned char getKD(Drive *drive);

#endif