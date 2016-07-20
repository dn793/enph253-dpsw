// Pins.h

#ifndef _PINS_h
#define _PINS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//Digital input pins
#define RIGHT_NODE			0
#define FRONT_RIGHT_LINE	1
#define FRONT_LEFT_LINE		2
#define LEFT_NODE			3
#define EDGE				4
#define	COLLISION_FRONT		5
#define	COLLISION_BACK		6
#define TILT_SWITCH			7
#define ROTATE_SWITCH		8
#define	CLAW_SWITCH			9
#define LEFT_SENSOR_ARRAY	10	
#define RIGHT_SENSOR_ARRAY	11
//#define 					12
//#define 					13
#define BASE_ROTATION_QRD	14
#define ARM_EXTENSION		15


//Analog input pins
#define FRONT_LEFT_IR		0
#define BACK_LEFT_IR		1
#define FRONT_RIGHT_LINE	2
#define BACK_RIGHT_IR		3
#define LEFT_BEACON_IR		4
#define RIGHT_BEACON_IR		5
#define CENTRE_SENSOR_ARRAY	6
#define KNOB				7

//Motor outputs
#define RIGHT_WHEEL		0
#define LEFT_WHEEL		1
#define ROTATING_BASE	2
#define ARM_EXTENSION	3

//Servo motor outputs
#define ARM_TILT	0
#define CLAW		1


#endif

