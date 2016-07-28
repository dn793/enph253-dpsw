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
	else /* (!(leftLine) && !(rightLine)) */
	{
		if (lastError > 0) { error = 5; }
		else if (lastError <= 0) { error = -5; }
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
	if (velocity - corr < -MAX_SPEED) { velocity = -MAX_SPEED; }
	if (velocity + corr > MAX_SPEED)	{ velocity = MAX_SPEED; }
 
	if (nodeDetect() != 0) { return moveToNextNode(); }

	if (digitalRead(EDGE)) { return DETECT_EDGE; }
	else
	{
		motor.speed(RIGHT_WHEEL, velocity - corr);
		motor.speed(LEFT_WHEEL, velocity + corr);
	}
 
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
void Drive::turnLeft()
{
	motor.speed(RIGHT_WHEEL, MAX_SPEED - 50);
	motor.speed(LEFT_WHEEL, -50);
	bool passedLine = false;

	delay(DELAY_TURN);

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
 * Turns the robot to the right, robot turns about right wheel.
 */
void Drive::turnRight()
{
	motor.speed(RIGHT_WHEEL, -50);
	motor.speed(LEFT_WHEEL, MAX_SPEED - 50);
	bool passedLine = false;

	delay(DELAY_TURN);
	
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
 * Makes the robot do a 180 degree turn (turns to the left, about its centre axis).
 */
void Drive::turnAroundLeft()
{
	motor.speed(RIGHT_WHEEL, MAX_SPEED / 2);
	motor.speed(LEFT_WHEEL, -MAX_SPEED / 2);
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
	motor.speed(RIGHT_WHEEL, -MAX_SPEED);
	motor.speed(LEFT_WHEEL, MAX_SPEED);
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
	unsigned char right = digitalRead(RIGHT_NODE);
	unsigned char left = digitalRead(LEFT_NODE);

	if (right && left) { return DETECT_NODE_BOTH; }
	if (right) { return DETECT_NODE_RIGHT; }
	if (left) { return DETECT_NODE_LEFT; }
	
	return 0;
}

/*
 * Detects collisions.
 * Requires that collision sensors input high when there is a collision.
 */
char Drive::collisionDetect()
{
	if (digitalRead(COLLISION_FRONT)) { return DETECT_COLLISION_FRONT; }
	// if (digitalRead(COLLISION_BACK)) { return DETECT_COLLISION_BACK; }
	
	return 0;
}

/*
 * Turns the robot around if off the edge.
 */
void Drive::backToSurface()
{	
	reverse(-MAX_SPEED/2);
	delay(DELAY_STOP * 2);
	stop();
	turnAroundLeft();
	
	if (digitalRead(EDGE)) { stop(); backToSurface(); }
}

/*
 * Checks for passengers on each side of the road
*/
int Drive::passengerDetect() {

	double leftIR = analogRead(FRONT_LEFT_IR) * 5.0 / 1023.0;
	double rightIR = analogRead(FRONT_RIGHT_IR) * 5.0 / 1023.0;

	if (leftIR >= PASSENGER_THRESHOLD) { return DETECT_PASSENGER_LEFT; }
	if (rightIR >= PASSENGER_THRESHOLD) { return DETECT_PASSENGER_RIGHT; }
	
	return 0;
}

/*
 * Gives direction/decision of movement at an intersection, based on the next node in the path.
 * Assumes that the path is not empty.
 */
unsigned char Drive::moveToNextNode()
{
	std::vector<unsigned char> adjacents = getAdjacentNodes(currentNode);

	// If nextNode is not adjacent, build path towards it
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
	else
	{
		// Find direction of travel relative to current node
		unsigned char nextIndex;
		for (unsigned char i = 0; i < adjacents.size(); ++i)
		{
			if (adjacents[i] == nextNode) { nextIndex = i; break; }
		}
		nextDirection = getAdjacentDirections(currentNode)[nextIndex];

		// Relate absolute direction to relative direction of movement
		unsigned char action;
		switch (getRelativeDirection(currentDirection, nextDirection))
		{
		case NORTH: { action = CHOOSE_STRAIGHT; }
		case SOUTH: { action = CHOOSE_BACK; }
		case WEST: { action = CHOOSE_LEFT; }
		case EAST: { action = CHOOSE_RIGHT; }
		}

		// Find absolute direction of robot relative to destination
		adjacents = getAdjacentNodes(nextNode);
		unsigned char currentIndex;
		for (unsigned char i = 0; i < adjacents.size(); ++i)
		{
			if (adjacents[i] == currentNode) { currentIndex = i; break; }
		}

		// Transition variables to next state
		lastDirection = currentDirection;
		currentDirection = getAdjacentDirections(nextNode)[currentIndex];
		lastNode = currentNode;
		currentNode = nextNode;
		nextNode = path.front(); path.pop_front();

		return action;
	}
}