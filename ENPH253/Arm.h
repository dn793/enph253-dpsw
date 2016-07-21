#ifndef arm_h
#define arm_h

#include <phys253.h>
#include "Pins.h"

#define CENTER_SENSOR_ARRAY				6
#define RIGHT_SENSOR_ARRAY				11
#define LEFT_SENSOR_ARRAY				10
#define PLATFORM_THRESHOLD				5
#define PASSENGER_DETECTED_THRESHOLD	3
#define TOPLEFT_PASS_DETECT				1
#define BOTTOMLEFT_PASS_DETECT			2
#define TOPRIGHT_PASS_DETECT			3
#define BOTTOMRIGHT_PASS_DETECT			4
#define ARM_START_ROT_SPEED				200
#define ARM_START_EXT_SPEED				200
#define BACK							-1
#define FWD								1
#define FULL_EXTENSION_TIME             3000

/*
 * Pick up passenger.
 */
void pickupPassenger();

/*
 * Check if passenger is present.
 * Returns 0 for no passenger, 1 for passenger on right , -1 for passenger on left
 */
int detectPassenger();

/*
 * Moves arm to starting position to begin search for passenger.
 * @param state: the current passenger detection state, -1 for left and 1 for right
*/
void startArm(int state);

/*
 * Rotates arm to platform to find a rough position to begin PID finding.
 * Returns false if none found.
*/
bool rotateBasePID(int state);

/*
 * Extends claw to a passenger, its max distance, or a set threshold.
 * Returns true if the claw switch is pressed.
 */
bool armPID(int state);

/*
 * Extends or retracts the arm.
 */
void moveArm(int direction);

/*
 * Returns the arm to its home position.
 * Assume already on clear start search position or arm is already retracted.
 */
void moveArmHome(int state, bool havePassenger);

/*
 * Stops rotation or extension of the arm. 
 */
void stopArmNow(int motorVal, int velocity);

#endif