// Drive.h

#ifndef _DRIVE_h
#define _DRIVE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define MAX_SPEED	255

class Drive
{
	public:
		Drive();
		void lineFollow();
		void turnLeft();
		void turnRight();
		void hardLeft();
		void hardRight();
		void turnAround();
		void driveForward(int speed);
		void reverse(int speed);
		void stop();
		void stopNow();
		void setKP();
		void setKD();
		int getKP();
		int getKD();
	private:
		//QRD sensors
		int rightLine;
		int leftLine;
		int rightNode;
		int leftNode;
		int edge;

		//PID variables
		double kp;
		double kd;
		double der;
		double prop;
		double corr;
		double error = 0;
		double prevError = 0;
		double lastError = 0;
		//other variables
		double velocity;
		double q;
		double m;
};
#endif

