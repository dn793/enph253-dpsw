#include "Drive.h"

Drive::Drive()
{
	kp = INITIAL_KP;
	kd = INITIAL_KD;
	error = 0;
	prevError = 0;
	lastError = 0;
	q = 1;
	m = 0;
}

/*
 * Line following functionality.
 * Includes intersection detection and action.
 */
unsigned char Drive::lineFollow()
{
	if (digitalRead(EDGE)) { return DETECT_EDGE; }

	rightLine = digitalRead(FRONT_RIGHT_LINE);
	leftLine = digitalRead(FRONT_LEFT_LINE);
    
	if (nodeDetect() != 0) { return moveToNextNode(); }

	if (leftLine && rightLine) { error = 0; }
	else if (leftLine && !(rightLine)) { error = -1; }
	else if (!(leftLine) && rightLine) { error = 1; }
	else
	{
		if (lastError > 0) { error = 5; }
		else { error = -5; }
	}

	if (error != lastError)
	{
		prevError = lastError;
		q = m;
		m = 1;
	}
	lastError = error;

	prop = kp * error;
	der = (float)kd * (error - prevError) / (q +  m);
	corr = prop + der;
	++m;

	velocity = INITIAL_VELOCITY;
	if (velocity - corr < MAX_SPEED * -1) { velocity = MAX_SPEED * -1; }
	if (velocity + corr > MAX_SPEED) { velocity = MAX_SPEED; }
 
	if (nodeDetect() != 0) { return moveToNextNode(); }

	if (digitalRead(EDGE)) { return DETECT_EDGE; }
	
	motor.speed(RIGHT_WHEEL, velocity - corr);
	motor.speed(LEFT_WHEEL, velocity + corr);
 
	return 0;
}

/*
 * Drive the robot straight forward; does NOT line follow.
 * @param speed: speed of robot is between 0 and 255.
 */
void Drive::driveForward(unsigned char speed)
{
	motor.speed(RIGHT_WHEEL, speed);
	motor.speed(LEFT_WHEEL, speed);
}

/*
 * Drive the robot straight backwards; does NOT line follow.
 * @param speed: speed of robot is between 0 and -255.
 */
void Drive::reverse(short speed)
{
	motor.speed(RIGHT_WHEEL, speed);
	motor.speed(LEFT_WHEEL, speed);
}

/*
 * Turns the robot to the left, robot turns about left wheel.
 */
bool Drive::turnLeft()
{
	bool passedLine = false;
	bool trueTurn = (digitalRead(RIGHT_OUTER_NODE) || digitalRead(LEFT_OUTER_NODE)) ? true : false;
	
	motor.speed(RIGHT_WHEEL, MAX_SPEED - TURN_SPEED);
	motor.speed(LEFT_WHEEL, TURN_SPEED * -1);

	unsigned long startTime = millis();
	while (millis() - startTime < DELAY_TURN)
	{
		if (digitalRead(RIGHT_OUTER_NODE) || digitalRead(LEFT_OUTER_NODE)) {
			trueTurn = true;
		}
	}

	while(!passedLine)
	{
		if (digitalRead(RIGHT_OUTER_NODE) || digitalRead(LEFT_OUTER_NODE)) {
			trueTurn = true;
		}

		passedLine = digitalRead(FRONT_RIGHT_LINE);
		if (passedLine)
		{
			error = 1;
			prevError = 1;
			lastError = 1;
			q = 1;
			m = 0;
			stop();
			break;
		}
    
		passedLine = digitalRead(FRONT_LEFT_LINE);
		if (passedLine)
		{
			error = -1;
			prevError = -1;
			lastError = -1;
			q = 1;
			m = 0;
			stop();
			break;
		}
	}

	return trueTurn;
}

/*
 * Turns the robot to the right, robot turns about right wheel.
 */
bool Drive::turnRight()
{
	bool passedLine = false;
	bool trueTurn = (digitalRead(RIGHT_OUTER_NODE) || digitalRead(LEFT_OUTER_NODE)) ? true : false;

	motor.speed(RIGHT_WHEEL, TURN_SPEED * -1);
	motor.speed(LEFT_WHEEL, MAX_SPEED - TURN_SPEED);

	unsigned long startTime = millis();
	while (millis() - startTime < DELAY_TURN)
	{
		if (digitalRead(RIGHT_OUTER_NODE) || digitalRead(LEFT_OUTER_NODE)) { trueTurn = true; }
	}

	motor.speed(RIGHT_WHEEL, -50);
	motor.speed(LEFT_WHEEL, MAX_SPEED - 50);

	delay(DELAY_TURN);
	
	while (!passedLine)
	{
		if (digitalRead(RIGHT_OUTER_NODE) || digitalRead(LEFT_OUTER_NODE)) { trueTurn = true; }

		passedLine = digitalRead(FRONT_LEFT_LINE);
		if (passedLine)
		{
			error = -1;
			prevError = -1;
			lastError = -1;
			q = 1;
			m = 0;
			stop();
			break;
		}

		passedLine = digitalRead(FRONT_RIGHT_LINE);
		if (passedLine)
		{
			error = 1;
			prevError = 1;
			lastError = 1;
			q = 1;
			m = 0;
			stop();
			break;
		}
	}

	return trueTurn;
}

/*
 * Makes the robot do a 180 degree turn (turns to the left, about its centre axis).
 */
void Drive::turnAroundLeft()
{
	motor.speed(RIGHT_WHEEL, MAX_SPEED / 2);
	motor.speed(LEFT_WHEEL, MAX_SPEED / -2);
    bool passedLine = false;

	delay(DELAY_ROTATE);
	while(!passedLine)
	{
		passedLine = digitalRead(FRONT_RIGHT_LINE);
		if (passedLine)
		{
			error = 1;
			prevError = 1;
			lastError = 1;
			q = 1;
			m = 0;
			stop();
			break;
		}

		passedLine = digitalRead(FRONT_LEFT_LINE);
		if (passedLine)
		{
			error = -1;
			prevError = -1;
			lastError = -1;
			q = 1;
			m = 0;
			stop();
			break;
		}
    }
}

/*
 * Makes the robot do a 180 degree turn (turns to the right, about its centre axis).
 */
void Drive::turnAroundRight()
{
	motor.speed(RIGHT_WHEEL, MAX_SPEED / -2);
	motor.speed(LEFT_WHEEL, MAX_SPEED / 2);
	bool passedLine = false;

	delay(DELAY_ROTATE);
	while (!passedLine)
	{
		passedLine = digitalRead(FRONT_LEFT_LINE);
		if (passedLine)
		{
			error = -1;
			prevError = -1;
			lastError = -1;
			q = 1;
			m = 0;
			stop();
			break;
		}

		passedLine = digitalRead(FRONT_RIGHT_LINE);
		if (passedLine)
		{
			error = 1;
			prevError = 1;
			lastError = 1;
			q = 1;
			m = 0;
			stop();
			break;
		}
	}
}

/*
 * Decides which way to turn around based on position/orientation of the robot.
 */
void Drive::turnAround()
{
	if (currentNode <= 4 || (currentNode == 14 && currentDirection == EAST))
	{
		turnAroundLeft();
		return;
	}
	
	turnAroundRight();
}

/* 
 * Stops the robot.
 */
void Drive::stop() { motor.stop(RIGHT_WHEEL); motor.stop(LEFT_WHEEL); }

/*
 * Stops the robot immediately.
 */
void Drive::stopNow()
{
	motor.speed(LEFT_WHEEL, -MAX_SPEED);
	motor.speed(RIGHT_WHEEL, -MAX_SPEED);
	delay(DELAY_STOP);
	motor.stop(LEFT_WHEEL);
	motor.stop(RIGHT_WHEEL);
}

/*
* Turns the robot around if off the edge.
*/
void Drive::backToSurface()
{
	reverse(MAX_SPEED / -2);
	delay(DELAY_STOP * 2);
	stop();
	turnAround();

	if (digitalRead(EDGE)) { stop(); backToSurface(); }
}

/*
 * Set the proportional constant.
 */
void Drive::setKP(unsigned char value) { kp = value; }

/*
 * Set the derivative constant.
 */
void Drive::setKD(unsigned char value) { kd = value; }

/*
 * Returns the proportional constant.
 */
unsigned char Drive::getKP() { return kp; }

/*
 * Returns the derivative constant.
 */
unsigned char Drive::getKD() { return kd; }

/*
 * Reads QRD sensors to check for intersection point.
 */
char Drive::nodeDetect()
{
	unsigned char rightNode = digitalRead(RIGHT_NODE);
	unsigned char leftNode = digitalRead(LEFT_NODE);

	if (rightNode && leftNode) { return DETECT_NODE_BOTH; }
	if (rightNode) { return DETECT_NODE_RIGHT; }
	if (leftNode) { return DETECT_NODE_LEFT; }
	
	return 0;
}

/*
 * Detects collisions.
 * Requires that collision sensors input high when there is a collision.
 */
char Drive::collisionDetect()
{
	if (!digitalRead(COLLISION_FRONT)) { return DETECT_COLLISION_FRONT; }
	if (digitalRead(COLLISION_BACK)) { return DETECT_COLLISION_BACK; }
	
	return 0;
}

/*
 * Checks for passengers on each side of the road
*/
char Drive::passengerDetect()
{
	float leftIR = analogRead(BACK_LEFT_IR) * 5 / 1023;
	float rightIR = analogRead(BACK_RIGHT_IR) * 5 / 1023;

	if (leftIR >= PASSENGER_THRESHOLD) { return DETECT_PASSENGER_LEFT; }
	if (rightIR >= PASSENGER_THRESHOLD) { return DETECT_PASSENGER_RIGHT; }
	
	return 0;
}


/*
 * Detects passengers by comparing each voltage to the previous voltages read;
 * if differences are sufficient, a passenger will be detected.
 */
char Drive::passengerCompare()
{
	float leftIR = analogRead(BACK_LEFT_IR) * 5 / 1023;
	float rightIR = analogRead(BACK_RIGHT_IR) * 5 / 1023;

	if ((leftIR - leftIRVal) < PASSENGER_DETECT_DIFFERENCE && leftIR > PASSENGER_THRESHOLD)
	{
		delay(DELAY_IR_PASS);
		leftIRVal = 0;
		return DETECT_PASSENGER_LEFT;
	}

	if ((rightIR - rightIRVal) < PASSENGER_DETECT_DIFFERENCE && rightIR > PASSENGER_THRESHOLD)
	{
		delay(DELAY_IR_PASS);
		rightIRVal = 0;
		return DETECT_PASSENGER_RIGHT;
	}

	if (leftIR > (PASSENGER_DETECT_DIFFERENCE - 0.5) && leftIR > leftIRVal)
	{
		leftIRVal = leftIR;
		delay(DELAY_IR_DETECT);
	}
	else { leftIRVal = 0; delay(DELAY_IR_DETECT); }

	if (rightIR > (PASSENGER_DETECT_DIFFERENCE - 0.5) && rightIR > rightIRVal)
	{
		rightIRVal = rightIR;
		delay(DELAY_IR_DETECT);
	}
	else { rightIRVal = 0; delay(DELAY_IR_DETECT); }

	return 0;
}

/*
 * Gives direction/decision of movement at an intersection, based on the next node in the path.
 * Assumes that the path is not empty.
 */
unsigned char Drive::moveToNextNode()
{
	// If already at next node, move to next node in path
	if (nextNode == currentNode)
	{
		nextNode = path.front();
		path.pop_front();
		return moveToNextNode();
	}

	std::vector<unsigned char> adjacents = getAdjacentNodes(currentNode);

	// If next node is not adjacent, build path towards it
	if (std::find(adjacents.begin(), adjacents.end(), nextNode) == adjacents.end())
	{
		std::vector<unsigned char> route = findShortestPath(currentNode, nextNode);
		for (std::vector<unsigned char>::reverse_iterator rit = route.rbegin(); rit != route.rend(); ++rit)
		{
			path.push_front(*rit);
		}
		nextNode = path.front();
		return moveToNextNode();
	}
	
	// Find direction of travel relative to current node
	unsigned char nextIndex;
	for (unsigned char i = 0; i < adjacents.size(); ++i)
	{
		if (adjacents[i] == nextNode) { nextIndex = i; break; }
	}
	nextDirection = getAdjacentDirections(currentNode)[nextIndex];

	// Relate absolute direction to relative direction of movement
	switch (getRelativeDirection(currentDirection, nextDirection))
	{
	case NORTH: return CHOOSE_STRAIGHT;
	case SOUTH: return CHOOSE_BACK;
	case WEST: return CHOOSE_LEFT;
	case EAST: return CHOOSE_RIGHT;
	}

	return 0;
}

void Drive::moveToNextState()
{
	// Find absolute direction of robot relative to destination
	std::vector<unsigned char> adjacents = getAdjacentNodes(nextNode);
	unsigned char currentIndex;
	for (unsigned char i = 0; i < adjacents.size(); ++i)
	{
		if (adjacents[i] == currentNode) { currentIndex = i; break; }
	}

	// Transition variables to next state
	lastDirection = currentDirection;
	currentDirection = reverseDirection(getAdjacentDirections(nextNode)[currentIndex]);
	lastNode = currentNode;
	currentNode = nextNode;
	nextNode = path.front(); path.pop_front();
}