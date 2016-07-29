#include "Navigation.h"

/*
 * Returns nodes adjacent to specified node.
 */
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

/*
 * Returns directions of nodes adjacent to specified node.
 * Nodes are ordered identically to getAdjacentNodes() above.
 */
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

/*
 * Returns direction opposite to specified.
 */
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

/*
 * Returns relative orientation of robot direction given absolute/cardinal directions.
 */
unsigned char getRelativeDirection(unsigned char currentDirection, unsigned char nextDirection)
{
	if (currentDirection == SOUTH && nextDirection == NORTH) { return SOUTH; }
	if (currentDirection == SOUTH && nextDirection == WEST) { return EAST; }
	if (currentDirection == SOUTH && nextDirection == EAST) { return WEST; }
	if (currentDirection == SOUTH && nextDirection == SOUTH) { return NORTH; }
	if (currentDirection == WEST && nextDirection == WEST) { return NORTH; }
	if (currentDirection == WEST && nextDirection == EAST) { return SOUTH; }
	if (currentDirection == WEST && nextDirection == SOUTH) { return WEST; }
	if (currentDirection == WEST && nextDirection == NORTH) { return EAST; }
	if (currentDirection == EAST && nextDirection == EAST) { return NORTH; }
	if (currentDirection == EAST && nextDirection == SOUTH) { return EAST; }
	if (currentDirection == EAST && nextDirection == WEST) { return SOUTH; }
	if (currentDirection == EAST && nextDirection == NORTH) { return WEST; }

	return nextDirection;
}

/*
 * Uses breadth-first search to find the shortest path between two nodes.
 */
std::vector<unsigned char> findShortestPath(unsigned char source, unsigned char destinationNode)
{
	std::vector<bool> visited 
			= { false, false, false, false, false, false, false, false, false, false,
			    false, false, false, false, false, false, false, false, false, false };
	std::vector<unsigned char> previous
			= { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
			    255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
	
	std::deque<unsigned char> queue;
	queue.push_front(source);

	unsigned char currentNode;
	while (!queue.empty())
	{
		currentNode = queue.front();
		queue.pop_front();

		if (visited[currentNode - 1] == false)
		{
			visited[currentNode - 1] = true;

			if (currentNode == destinationNode) { queue.erase(queue.begin(), queue.end()); break; }
			
			for (unsigned char node : getAdjacentNodes(currentNode))
			{
				queue.push_back(node);
				if (previous[node - 1] == 255) { previous[node - 1] = currentNode; }
			}
		}
	}

	queue.push_back(destinationNode);
	while (previous[currentNode - 1] != source)
	{
		queue.push_front(previous[currentNode - 1]);
		currentNode = previous[currentNode - 1];
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

/*
 * Uses breadth-first search to find an alternate path between two adjacent nodes.
 */
std::vector<unsigned char> findAlternatePath(unsigned char source, unsigned char destinationNode)
{
	unsigned char newDestinationNode;
	std::vector<unsigned char> adjacentDestinations = getAdjacentNodes(destinationNode);
	if (source <= 10 && adjacentDestinations.back() != source) { newDestinationNode = adjacentDestinations.back(); }
	else if (source > 10 && adjacentDestinations.front() != source) { newDestinationNode = adjacentDestinations.front(); }
	else
	{
		for (unsigned char node : adjacentDestinations) { if (node != source) { newDestinationNode = node; } }
	}

	std::vector<bool> visited
		= { false, false, false, false, false, false, false, false, false, false,
		    false, false, false, false, false, false, false, false, false, false };
	std::vector<unsigned char> previous
		= { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		    255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };

	std::deque<unsigned char> queue;
	queue.push_front(source);

	unsigned char currentNode;
	while (!queue.empty())
	{
		currentNode = queue.front();
		queue.pop_front();

		if (visited[currentNode - 1] == false)
		{
			visited[currentNode - 1] = true;

			if (currentNode == destinationNode) { queue.erase(queue.begin(), queue.end()); break; }

			for (unsigned char node : getAdjacentNodes(currentNode))
			{
				queue.push_back(node);
				if (previous[node - 1] == 255) { previous[node - 1] = currentNode; }
			}
		}
	}

	queue.push_back(newDestinationNode);
	while (previous[currentNode - 1] != source)
	{
		queue.push_front(previous[currentNode - 1]);
		currentNode = previous[currentNode - 1];
	}

	std::vector<unsigned char> path;
	path.reserve(10);
	path.push_back(destinationNode);
	while (!queue.empty())
	{
		path.push_back(queue.front());
		queue.pop_front();
	}

	return path;
}

/*
 * Finds the shortest path to a drop-off node from the currentNode
 */
std::vector<unsigned char> getDropOffPath(unsigned char currentNode)
{
	unsigned char destinationNode;
	switch (currentNode)
	{
	case 1: destinationNode = 4; break;
	case 2: destinationNode = 4; break;
	case 3: destinationNode = 4; break;
	case 5: destinationNode = 4; break;
	case 6: destinationNode = 4; break;
	case 7: destinationNode = 4; break;
	case 8: destinationNode = 4; break;
	case 9: destinationNode = 4; break;
	case 10: destinationNode = 14; break;
	case 11: destinationNode = 14; break;
	case 12: destinationNode = 14; break;
	case 13: destinationNode = 14; break;
	case 15: destinationNode = 14; break;
	case 16: destinationNode = 14; break;
	case 17: destinationNode = 14; break;
	case 18: destinationNode = 14; break;
	case 19: destinationNode = 14; break;
	case 20: destinationNode = 14; break;
	}

	return findShortestPath(currentNode, destinationNode);
}