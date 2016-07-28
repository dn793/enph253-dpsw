#ifndef _NAVIGATION_h
#define _NAVIGATION_h

#include <avr/pgmspace.h>
#include <deque>
#include <vector>

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

const unsigned char weightMatrix[20][20] PROGMEM = {
	// 1
	{ 0, /* 2 */ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 2
	{/* 1 */ 2, 0, /* 3 */ 1, 0, /* 5 */ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 3
	{ 0, /* 2 */ 1, 0, /* 4 */ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 4
	{ 0, 0, /* 3 */ 2, 0, /* 5 */ 2, 0, 0, 0, 0, 0, 0, 0, 0, /* 14 */ 4, 0, 0, 0, 0, 0, 0 },
	// 5    
	{ 0, /* 2 */ 2, 0, /* 4 */ 2, 0, /* 6 */ 2, 0, 0, /* 9 */ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 6
	{ 0, 0, 0, 0, /* 5 */ 2, 0, /* 7 */ 3, /* 8 */ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 7
	{ 0, 0, 0, 0, 0, /* 6 */ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 8
	{ 0, 0, 0, 0, 0, /* 6 */ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 9
	{ 0, 0, 0, 0, /* 5 */ 1, 0, 0, 0, 0, /* 10 */ 2, 0, /* 12 */ 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 10
	{ 0, 0, 0, 0, 0, 0, 0, 0, /* 9 */ 2, 0, /* 11 */ 2, /* 12 */ 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 11
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 10 */ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 12
	{ 0, 0, 0, 0, 0, 0, 0, 0, /* 9 */ 2, /* 10 */ 2, 0, 0, /* 13 */ 1, 0, 0, 0, 0, 0, 0, 0 },
	// 13
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 12 */ 1, 0, /* 14 */ 2, /* 15 */ 2, 0, 0, 0, 0, /* 19 */ 2, 0 },
	// 14
	{ 0, 0, 0, /* 4 */ 4, 0, 0, 0, 0, 0, 0, 0, /* 13 */ 2, 0, 0, 0, 0, 0, /* 18 */ 2, 0, 0 },
	// 15
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 13 */ 2, 0, 0, /* 16 */ 3, /* 17 */ 3, 0, 0, 0 },
	// 16
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 15 */ 3, 0, 0, 0, 0, 0 },
	// 17
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 15 */ 3, 0, 0, 0, 0, 0 },
	// 18
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 14 */ 2, 0, 0, 0, 0, /* 19 */ 1, 0 },
	// 19
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 18 */ 1, /* 20 */ 2 },
	// 20
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 19 */ 2, 0 }
};

unsigned char getWeight(unsigned char current, unsigned char adjacent);

std::vector<unsigned char> getAdjacentNodes(unsigned char node);

std::vector<unsigned char> getAdjacentDirections(unsigned char node);

unsigned char reverseDirection(unsigned char direction);

unsigned char getRelativeDirection(unsigned char currentDirection, unsigned char nextDirection);

std::vector<unsigned char> findShortestPath(unsigned char source, unsigned char destination);

std::vector<unsigned char> getDropOffPath(unsigned char current);

#endif