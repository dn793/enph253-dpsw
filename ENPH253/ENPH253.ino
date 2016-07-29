#include <phys253.h>
#include <StandardCplusplus.h>
#include <LiquidCrystal.h>

#include "Pins.h"
#include "Arm.h"
#include "Drive.h"
#include "Navigation.h"

Drive robotDriver;
Arm robotArm;
unsigned char lineFollowResult;

void setup()
{
	#include <phys253setup.txt>
	Serial.begin(115200);
	motor.stop_all();
	LCD.clear();

	if (knob(KNOB) <= 1023 / 2)
	{
		robotDriver.currentNode = 1;
		robotDriver.path.push_back(2);
		robotDriver.path.push_back(5);
		robotDriver.path.push_back(4);
		robotDriver.path.push_back(5);
		robotDriver.path.push_back(8);
		robotDriver.path.push_back(0);
	}
	else
	{
		robotDriver.currentNode = 20;
		robotDriver.path.push_back(19);
		robotDriver.path.push_back(13);
		robotDriver.path.push_back(14);
		robotDriver.path.push_back(4);
		robotDriver.path.push_back(5);
		robotDriver.path.push_back(9);
		robotDriver.path.push_back(12);
		robotDriver.path.push_back(0);
	}
	robotDriver.currentDirection = SOUTH;
	robotDriver.nextDirection = SOUTH;
	robotDriver.nextNode = robotDriver.path.front();
	robotDriver.path.pop_front();
}

void loop()
{
	while (startbutton())
	{
		robotDriver.setKP(knob(6) / 10);
		LCD.clear(); LCD.setCursor(0, 0); LCD.print("kp: "); LCD.print(robotDriver.getKP());
		delay(1000);
	}

	while (stopbutton())
	{
		robotDriver.setKD(knob(KNOB) / 10);
		LCD.clear(); LCD.setCursor(0, 0); LCD.print("kd: "); LCD.print(robotDriver.getKD());
		delay(1000);
	}

	if (robotDriver.nextNode == PATH_END)
	{
		LCD.clear();
		LCD.setCursor(0, 0); LCD.print("Path empty");
		LCD.setCursor(0, 1); LCD.print("Last node: "); LCD.print(robotDriver.lastNode);
		robotDriver.stop();
	}
	else
	{
		switch (robotDriver.collisionDetect())
		{
		case DETECT_COLLISION_FRONT:
		{
			LCD.clear(); LCD.setCursor(0, 0); LCD.print("COLLISION FRONT");
			robotDriver.stop();
			std::vector<unsigned char> newRoute = findAlternatePath(robotDriver.currentNode, robotDriver.nextNode);
			for (std::vector<unsigned char>::reverse_iterator rit = newRoute.rbegin(); rit != newRoute.rend(); ++rit)
			{
				robotDriver.path.push_front(*rit);
			}
			robotDriver.nextNode = robotDriver.path.front();
			robotDriver.backToSurface();
			break;
		}
		case DETECT_COLLISION_BACK:
		{
			LCD.clear(); LCD.setCursor(0, 0); LCD.print("COLLISION REAR");
			robotDriver.stop();
			break;
		}
		default: break;
		}

		switch (robotDriver.passengerDetect())
		{
		case DETECT_PASSENGER_RIGHT:
			LCD.clear(); LCD.setCursor(0, 0); LCD.print("PASSENGER RIGHT");
			robotDriver.stop();
			/*while (robotDriver.passengerDetect() == DETECT_PASSENGER_RIGHT) {

			}
			delay(1300);*/
			break;
		case DETECT_PASSENGER_LEFT:
			LCD.clear(); LCD.setCursor(0, 0); LCD.print("PASSENGER LEFT");
			robotDriver.stop();
			/*while (robotDriver.passengerDetect() == DETECT_PASSENGER_LEFT) {

			}
			delay(1300);*/
			break;
		default: break;
		}

		LCD.clear();
		LCD.setCursor(0, 0);
		LCD.print("CURR: ");
		LCD.print(robotDriver.currentNode);
		LCD.print(" ");
		LCD.print(robotDriver.currentDirection);
		LCD.print(" NEXT: ");
		LCD.print(robotDriver.nextNode);
		LCD.print(" ");
		LCD.print(robotDriver.nextDirection);

		lineFollowResult = robotDriver.lineFollow();

		if (lineFollowResult >= CHOOSE_STRAIGHT) { robotDriver.moveToNextState(); }

		switch (lineFollowResult)
		{
		case DETECT_EDGE: LCD.setCursor(0, 1); LCD.print("EDGE"); robotDriver.backToSurface(); break;
		case CHOOSE_STRAIGHT: LCD.setCursor(0, 1); LCD.print("STRAIGHT"); robotDriver.driveForward(MAX_SPEED); break;
		case CHOOSE_BACK: LCD.setCursor(0, 1); LCD.print("BACK"); robotDriver.turnAround(); break;
		case CHOOSE_LEFT: LCD.setCursor(0, 1); LCD.print("LEFT"); robotDriver.turnLeft(); break;
		case CHOOSE_RIGHT: LCD.setCursor(0, 1); LCD.print("RIGHT"); robotDriver.turnRight(); break;
		default: break;
		}


	}
}
