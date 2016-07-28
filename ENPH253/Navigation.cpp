#include "Navigation.h"

unsigned char getWeight(unsigned char current, unsigned char adjacent)
{	return (unsigned char)weightMatrix[current - 1][adjacent - 1]; }

std::vector<unsigned char> getAdjacentNodes(unsigned char node)
{
	std::vector<unsigned char> adjacents;
	adjacents.reserve(4);

	switch (node)
	{
	case 1:
		adjacents.push_back(2);
		break;
	case 2:
		adjacents.push_back(1);
		adjacents.push_back(3);
		adjacents.push_back(5);
		break;
	case 3:
		adjacents.push_back(2);
		adjacents.push_back(4);
		break;
	case 4:
		adjacents.push_back(3);
		adjacents.push_back(5);
		adjacents.push_back(14);
		break;
	case 5:
		adjacents.push_back(2);
		adjacents.push_back(4);
		adjacents.push_back(6);
		adjacents.push_back(9);
		break;
	case 6:
		adjacents.push_back(5);
		adjacents.push_back(7);
		adjacents.push_back(8);
		break;
	case 7:
		adjacents.push_back(6);
		break;
	case 8:
		adjacents.push_back(6);
		break;
	case 9:
		adjacents.push_back(5);
		adjacents.push_back(10);
		adjacents.push_back(12);
		break;
	case 10:
		adjacents.push_back(9);
		adjacents.push_back(11);
		adjacents.push_back(12);
		break;
	case 11:
		adjacents.push_back(10);
		break;
	case 12:
		adjacents.push_back(10);
		adjacents.push_back(13);
		break;
	case 13:
		adjacents.push_back(12);
		adjacents.push_back(14);
		adjacents.push_back(15);
		adjacents.push_back(19);
		break;
	case 14:
		adjacents.push_back(4);
		adjacents.push_back(13);
		adjacents.push_back(18);
		break;
	case 15:
		adjacents.push_back(13);
		adjacents.push_back(16);
		adjacents.push_back(17);
		break;
	case 16:
		adjacents.push_back(15);
		break;
	case 17:
		adjacents.push_back(15);
		break;
	case 18:
		adjacents.push_back(14);
		adjacents.push_back(19);
		break;
	case 19:
		adjacents.push_back(13);
		adjacents.push_back(18);
		adjacents.push_back(20);
		break;
	case 20:
		adjacents.push_back(19);
		break;
	}

	return adjacents;
}

std::vector<unsigned char> getAdjacentDirections(unsigned char node)
{
	std::vector<unsigned char> directions;
	directions.reserve(4);

	switch (node)
	{
	case 1:
		directions.push_back(SOUTH);
		break;
	case 2:
		directions.push_back(NORTH);
		directions.push_back(SOUTH);
		directions.push_back(EAST);
		break;
	case 3:
		directions.push_back(NORTH);
		directions.push_back(EAST);
		break;
	case 4:
		directions.push_back(WEST);
		directions.push_back(NORTH);
		directions.push_back(EAST);
		break;
	case 5:
		directions.push_back(WEST);
		directions.push_back(SOUTH);
		directions.push_back(NORTH);
		directions.push_back(EAST);
		break;
	case 6:
		directions.push_back(SOUTH);
		directions.push_back(WEST);
		directions.push_back(NORTH);
		break;
	case 7:
		directions.push_back(EAST);
		break;
	case 8:
		directions.push_back(SOUTH);
		break;
	case 9:
		directions.push_back(WEST);
		directions.push_back(NORTH);
		directions.push_back(EAST);
		break;
	case 10:
		directions.push_back(WEST);
		directions.push_back(NORTH);
		directions.push_back(EAST);
		break;
	case 11:
		directions.push_back(SOUTH);
		break;
	case 12:
		directions.push_back(WEST);
		directions.push_back(EAST);
		break;
	case 13:
		directions.push_back(WEST);
		directions.push_back(SOUTH);
		directions.push_back(NORTH);
		directions.push_back(EAST);
		break;
	case 14:
		directions.push_back(WEST);
		directions.push_back(NORTH);
		directions.push_back(EAST);
		break;
	case 15:
		directions.push_back(SOUTH);
		directions.push_back(EAST);
		directions.push_back(NORTH);
		break;
	case 16:
		directions.push_back(WEST);
		break;
	case 17:
		directions.push_back(SOUTH);
		break;
	case 18:
		directions.push_back(WEST);
		directions.push_back(NORTH);
		break;
	case 19:
		directions.push_back(WEST);
		directions.push_back(SOUTH);
		directions.push_back(NORTH);
		break;
	case 20:
		directions.push_back(SOUTH);
		break;
	}

	return directions;
}

unsigned char reverseDirection(unsigned char direction)
{
	switch (direction)
	{
	case NORTH: return SOUTH;
	case SOUTH: return NORTH;
	case WEST: return EAST;
	case EAST: return WEST;
	}
}

unsigned char getRelativeDirection(unsigned char currentDirection, unsigned char nextDirection)
{
	if (currentDirection = SOUTH && nextDirection == NORTH) { return SOUTH; }
	else if (currentDirection = SOUTH && nextDirection == WEST) { return EAST; }
	else if (currentDirection = SOUTH && nextDirection == EAST) { return WEST; }
	else if (currentDirection = SOUTH && nextDirection == SOUTH) { return NORTH; }
	else if (currentDirection = WEST && nextDirection == WEST) { return NORTH; }
	else if (currentDirection = WEST && nextDirection == EAST) { return SOUTH; }
	else if (currentDirection = WEST && nextDirection == SOUTH) { return EAST; }
	else if (currentDirection = WEST && nextDirection == NORTH) { return WEST; }
	else if (currentDirection = EAST && nextDirection == EAST) { return NORTH; }
	else if (currentDirection = EAST && nextDirection == SOUTH) { return WEST; }
	else if (currentDirection = EAST && nextDirection == WEST) { return SOUTH; }
	else if (currentDirection = EAST && nextDirection == NORTH) { return EAST; }

	return nextDirection;
}

std::vector<unsigned char> findShortestPath(unsigned char source, unsigned char destination)
{
	std::vector<bool> visited 
			= { false, false, false, false, false, false, false, false, false, false,
			    false, false, false, false, false, false, false, false, false, false };
	std::vector<unsigned char> previous
			= { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
			    255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
	
	std::deque<unsigned char> queue;
	queue.push_front(source);

	unsigned char current;
	while (!queue.empty())
	{
		current = queue.front();
		queue.pop_front();

		if (visited[current - 1] == false)
		{
			visited[current - 1] = true;

			if (current == destination)
			{
				queue.erase(queue.begin(), queue.end());
				break;
			}
			
			for (unsigned char node : getAdjacentNodes(current))
			{
				queue.push_back(node);
				if (previous[node - 1] == 255) { previous[node - 1] = current; }
			}
		}
	}

	queue.push_back(destination);
	while (previous[current - 1] != source)
	{
		queue.push_front(previous[current - 1]);
		current = previous[current - 1];
	}

	std::vector<unsigned char> path;
	path.reserve(10);
	while (!queue.empty())
	{
		path.push_back(queue.front());
		queue.pop_front();
	}

	return path;
}

std::vector<unsigned char> getDropOffPath(unsigned char current)
{
	unsigned char destination;
	switch (current)
	{
	case 1: destination = 4; break;
	case 2: destination = 4; break;
	case 3: destination = 4; break;
	case 5: destination = 4; break;
	case 6: destination = 4; break;
	case 7: destination = 4; break;
	case 8: destination = 4; break;
	case 9: destination = 4; break;
	case 10: destination = 14; break;
	case 11: destination = 14; break;
	case 12: destination = 14; break;
	case 13: destination = 14; break;
	case 15: destination = 14; break;
	case 16: destination = 14; break;
	case 17: destination = 14; break;
	case 18: destination = 14; break;
	case 19: destination = 14; break;
	case 20: destination = 14; break;
	}

	return findShortestPath(current, destination);
}