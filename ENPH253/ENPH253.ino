#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <LiquidCrystal.h>
#include <phys253.h>
#include <motor.h>
#include <phys253pins.h>

#include "Arm.h"
#include "Collision.h"
#include "Drive.h"
#include "Pins.h"
#include "Navigation.c"

Drive * drive = createDrive();

unsigned char collisionState = 0;
unsigned char state = 1;
bool hasPassenger = false;
int direction = 1;


void setup() {
	#include <phys253setup.txt>
	Serial.begin(115200);
}

void loop() {
	
	// Detect collisions
	collisionState = getCollisionState();
	if (collisionState != 0) { collided(collisionState); }

	// Navigate and find passengers
	if (passengerDetected() && !carryingPassenger) { state = 1; }
	else if (DropOff()) { state = 2; }
	else { state = 3; }

	switch (state) {
		// Pick up passenger
		case 1:
		{
			pickUpPassenger();
			carryingPassenger = 1;
			break;
		}
			
		// Drop off passenger
		case 2:
		{
			navigate();
			dropOffPassenger();
			break;
		}
			
		// Detect passenger
		case 3:
		{
			if (detectIntersection()) { navigate(); }
			lineFollow();
			break;
		}		
	}
}
