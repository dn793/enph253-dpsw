#ifndef _ARM_h
#define _ARM_h

#include <phys253.h>
#include "Pins.h"

#define ARM_LEFT 1
#define ARM_RIGHT -1

#define DELAY_ARM_INIT 500
#define DELAY_STOP 30
#define DELAY_SWITCH 300
#define DELAY_ARM_CLOSE 40
#define DELAY_ARM_OPEN 500
#define DELAY_QRD_GRAB 250
#define DELAY_QRD_HOME 200

#define POS_ARM_OPEN 140
#define POS_ARM_CLOSED 40

#define SPEED_ROTATION_START 80
#define SPEED_EXTENSION_START 255 
#define SPEED_RETRACTION_START -255 

class Arm
{
public:
	Arm();
	void initialize();
	bool extendPickUp();
	void extendDropOff();
	bool close();
	void open();
	void stopNow(unsigned char motorVal, unsigned char velocity);
	void retract();
	bool rotateTo90(char dir);
	void rotateToHome(char dir);
private:
	bool havePassenger;
};

#endif

