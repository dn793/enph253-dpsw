#ifndef collision_h
#define collision_h

#include "Pins.h"
#include "Drive.h"

#define HIT_NONE 0
#define HIT_FRONT 1
#define HIT_BACK 2
#define HIT_BOTH 3
#define DELAY_HIT 200
#define SPEED_REVERSE 255

/*
 * Returns state of collision (front, back, both, or none).
 */
unsigned char getCollisionState();

/*
 * Either moves forwards or backwards depending on the collision state.
 * This prevents having to look for a lost digital signal.
 */
void collided(Drive *drive, unsigned char collisionState);

#endif
