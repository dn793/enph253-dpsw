#include <phys253.h>
#include <StandardCplusplus.h>
#include <LiquidCrystal.h>

//#include "Arm.h"
//#include "Collision.h"
#include "Drive.h"
#include "Navigation.h"
#include "Pins.h"

Drive robotDriver;
short edgeState = 0;
short isNode = 0;
float leftIR = 0;
float rightIR = 0;
float leftPassengerDetect = 0;
float rightPassengerDetect = 0;
bool havePassenger = false;

void setup()
{
	#include <phys253setup.txt>
	Serial.begin(115200);
	motor.stop_all();
}

void loop()
{
	while (startbutton())
	{
		LCD.clear();
		LCD.setCursor(0, 0);
		robotDriver.setKP(knob(6) / 10);
		LCD.print("kp: ");
		LCD.print(robotDriver.getKP());
		delay(1000);
	}

	while (stopbutton())
	{
		LCD.clear();
		LCD.setCursor(0, 0);
		robotDriver.setKD(knob(KNOB) / 10);
		LCD.print("kd: ");
		LCD.print(robotDriver.getKD());
		delay(1000);
	}

	if (robotDriver.path.empty()) { robotDriver.stop(); }
	else
	{
		switch (robotDrive.lineFollow())
		{
		case DETECT_EDGE:		robotDriver.backToSurface(); break;
		case CHOOSE_STRAIGHT:	robotDriver.driveForward(MAX_SPEED); break;
		case CHOOSE_BACK:		robotDriver.backToSurface(); break;
		case CHOOSE_LEFT:		robotDriver.turnLeft(); break;
		case CHOOSE_RIGHT:		robotDriver.turnRight(); break;
		default: break;
		}

		switch (robotDriver.passengerDetect())
		{
		case DETECT_PASSENGER_RIGHT:
			robotDriver.stop();
			LCD.clear();
			LCD.print("PASSENGER RIGHT");
			/*while (robotDriver.passengerDetect() == DETECT_PASSENGER_RIGHT) {

			}
			delay(1300);*/
			break;
		case DETECT_PASSENGER_LEFT:
			robotDriver.stop();
			LCD.clear();
			LCD.print("PASSENGER LEFT");
			/*while (robotDriver.passengerDetect() == DETECT_PASSENGER_LEFT) {

			}
			delay(1300);*/
			break;
		default: break;
		}

		switch (robotDriver.collisionDetect())
		{
		case DETECT_COLLISION_FRONT:
			robotDriver.stop();
			LCD.clear();
			LCD.print("collision");
			robotDriver.backToSurface();
			break;
		case DETECT_COLLISION_BACK:
			robotDriver.stop();
			LCD.clear();
			LCD.print("collision rear");
			break;
		default: break;
		}
	}
}