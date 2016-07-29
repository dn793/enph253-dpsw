#ifndef _NAVIGATION_h
#define _NAVIGATION_h

#include <deque>
#include <vector>

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

#define PATH_END 0

std::vector<unsigned char> getAdjacentNodes(unsigned char node);

std::vector<unsigned char> getAdjacentDirections(unsigned char node);

unsigned char reverseDirection(unsigned char direction);

unsigned char getRelativeDirection(unsigned char currentDirection, unsigned char nextDirection);

std::vector<unsigned char> findShortestPath(unsigned char source, unsigned char destinationNode);

std::vector<unsigned char> findAlternatePath(unsigned char source, unsigned char destinationNode);

std::vector<unsigned char> getDropOffPath(unsigned char current);

#endif