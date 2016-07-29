#ifndef _DRIVE_h
#define _DRIVE_h

#include <phys253.h>
#include "Navigation.h"
#include "Pins.h"

#define INITIAL_KP 9
#define INITIAL_KD 21
#define INITIAL_VELOCITY 125

#define MAX_SPEED 255
#define TURN_SPEED 50
#define PASSENGER_THRESHOLD	2.1
#define PASSENGER_DETECT_DIFFERENCE	-0.25

#define DELAY_TURN 200
#define DELAY_ROTATE 300
#define DELAY_STOP 25
#define DELAY_IR_PASS 1750
#define DELAY_IR_DETECT 10

#define DETECT_COLLISION_FRONT 1
#define DETECT_COLLISION_BACK -1
#define DETECT_EDGE 10
#define DETECT_NODE_LEFT -1
#define DETECT_NODE_RIGHT 1
#define DETECT_NODE_BOTH 2
#define DETECT_PASSENGER_LEFT -1
#define DETECT_PASSENGER_RIGHT 1

#define CHOOSE_STRAIGHT 40
#define CHOOSE_BACK 50
#define CHOOSE_LEFT 60
#define CHOOSE_RIGHT 70

class Drive
{
	public:
		Drive();
		unsigned char lineFollow();
		bool turnLeft();
		bool turnRight();
		void turnAroundLeft();
		void turnAroundRight();
		void turnAround();
		void driveForward(unsigned char speed);
		void reverse(short speed);
		void stop();
		void stopNow();
		void backToSurface();
		void setKP(unsigned char value);
		void setKD(unsigned char value);
		unsigned char getKP();
		unsigned char getKD();
		char nodeDetect();
		char collisionDetect();
		char passengerDetect();
		char passengerCompare();
		unsigned char moveToNextNode();
		void moveToNextState();

		std::deque<unsigned char> path;
		unsigned char lastNode;
		unsigned char currentNode;
		unsigned char nextNode;
		unsigned char lastDirection;
		unsigned char currentDirection;
		unsigned char nextDirection;
	private:
		// QRD sensors
		unsigned char rightLine;
		unsigned char leftLine;

		// PID variables
		double kp;
		double kd;
		short der;
		short prop;
		short corr;
		char error = 0;
		char prevError = 0;
		char lastError = 0;

		// Other variables
		short velocity;
		unsigned short q;
		unsigned short m;
		float leftIRVal;
		float rightIRVal;
};

#endif