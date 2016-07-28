#ifndef _DRIVE_h
#define _DRIVE_h

#include <phys253.h>
#include "Navigation.h"
#include "Pins.h"

#define INITIAL_KP 9
#define INITIAL_KD 21
#define INITIAL_VELOCITY 125

#define MAX_SPEED 255
#define PASSENGER_THRESHOLD	2.1

#define DELAY_TURN 200
#define DELAY_ROTATE 300
#define DELAY_STOP 25

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
		void turnLeft();
		void turnRight();
		void hardLeft();
		void hardRight();
		void turnAroundLeft();
		void turnAroundRight();
		void driveForward(unsigned char speed);
		void reverse(short speed);
		void stop();
		void stopNow();
		void setKP(unsigned char value);
		void setKD(unsigned char value);
		unsigned char getKP();
		unsigned char getKD();
		char nodeDetection();
		char collisionDetect();
		void backToSurface();
		char passengerDetect();
		unsigned char moveToNextNode();

		std::deque<unsigned char> path;

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

		// Navigation variables
		unsigned char lastNode;
		unsigned char currentNode;
		unsigned char nextNode;
		unsigned char lastDirection;
		unsigned char currentDirection;
		unsigned char nextDirection;

		// Other variables
		short velocity;
		unsigned short q;
		unsigned short m;
};

#endif