#ifndef graph_h
#define graph_h

#include <avr/pgmspace.h>

/*
 * Get weight of node with respect to current node.
 */
const unsigned char getWeight(unsigned char currentNode, unsigned char adjacentNode);

/*
 * Returns array of adjacent nodes.
 */
const unsigned char * getAdjacent(unsigned char node);

/*
 * Queue structure for nodes in path optimization.
 */
typedef struct Queue {
	unsigned char *queue;
	unsigned char size;
	unsigned char capacity;
	unsigned char front;
	unsigned char rear;
} Queue;

/*
 * Creates a Queue object with max capacity of 20.
 */
Queue * createQueue();

/*
 * Removes and returns first node from a Queue.
 */
unsigned char pop(Queue *q);

/*
 * Adds a node to the front of a Queue.
 */
void enqueue(Queue *q, unsigned char node);


/*
 * "Matrix" of weighted nodes.
 * Nodes are numbered as shown in "node layout.png".
 * 
 * Stored in flash memory.
 */
const unsigned char weightMatrix[20][20] PROGMEM = {
	// 1
	{ 0, /* 2 */ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 2
	{/* 1 */ 1, 0, /* 3 */ 1, 0, /* 5 */ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 3
	{ 0, /* 2 */ 1, 0, /* 4 */ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 4
	{ 0, 0, /* 3 */ 1, 0, /* 5 */ 1, 0, 0, 0, 0, 0, 0, 0, 0, /* 14 */ 1, 0, 0, 0, 0, 0, 0 },
	// 5    
	{ 0, /* 2 */ 1, 0, /* 4 */ 1, 0, /* 6 */ 1, 0, 0, /* 9 */ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 6
	{ 0, 0, 0, 0, /* 5 */ 1, 0, /* 7 */ 1, /* 8 */ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 7
	{ 0, 0, 0, 0, 0, /* 6 */ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 8
	{ 0, 0, 0, 0, 0, /* 6 */ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 9
	{ 0, 0, 0, 0, /* 5 */ 1, 0, 0, 0, 0, /* 10 */ 1, 0, /* 12 */ 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 10
	{ 0, 0, 0, 0, 0, 0, 0, 0, /* 9 */ 1, 0, /* 11 */ 1, /* 12 */ 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 11
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 10 */ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 12
	{ 0, 0, 0, 0, 0, 0, 0, 0, /* 9 */ 1, /* 10 */ 1, 0, 0, /* 13 */ 1, 0, 0, 0, 0, 0, 0, 0 },
	// 13
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 12 */ 1, 0, /* 14 */ 1, /* 15 */ 1, 0, 0, 0, 0, 0, 0 },
	// 14
	{ 0, 0, 0, /* 4 */ 1, 0, 0, 0, 0, 0, 0, 0, /* 13 */ 1, 0, 0, 0, 0, 0, /* 18 */ 1, 0, 0 },
	// 15
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 13 */ 1, 0, 0, /* 16 */ 1, /* 17 */ 1, 0, 0, 0 },
	// 16
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 15 */ 1, 0, 0, 0, 0, 0 },
	// 17
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 15 */ 1, 0, 0, 0, 0, 0 },
	// 18
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 14 */ 1, 0, 0, 0, 0, /* 19 */ 1, 0 },
	// 19
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 20 */ 1 },
	// 20
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 19 */ 1, 0 }
};

/*
 * Lists of adjacent nodes for each node.
 *
 * Stored in flash memory.
 */
const unsigned char adj_1[1] PROGMEM = { 2 };
const unsigned char adj_2[3] PROGMEM = { 1, 3, 5 };
const unsigned char adj_3[2] PROGMEM = { 2, 4 };
const unsigned char adj_4[3] PROGMEM = { 3, 5, 14 };
const unsigned char adj_5[4] PROGMEM = { 2, 4, 6, 9 };
const unsigned char adj_6[3] PROGMEM = { 5, 7, 8 };
const unsigned char adj_7[1] PROGMEM = { 6 };
const unsigned char adj_8[1] PROGMEM = { 6 };
const unsigned char adj_9[3] PROGMEM = { 5, 10, 12 };
const unsigned char adj_10[3] PROGMEM = { 9, 11, 12 };
const unsigned char adj_11[1] PROGMEM = { 10 };
const unsigned char adj_12[2] PROGMEM = { 10, 13 };
const unsigned char adj_13[4] PROGMEM = { 12, 14, 15, 19 };
const unsigned char adj_14[3] PROGMEM = { 4, 13, 18 };
const unsigned char adj_15[3] PROGMEM = { 13, 16, 17 };
const unsigned char adj_16[1] PROGMEM = { 15 };
const unsigned char adj_17[1] PROGMEM = { 15 };
const unsigned char adj_18[2] PROGMEM = { 14, 19 };
const unsigned char adj_19[3] PROGMEM = { 13, 18, 20 };
const unsigned char adj_20[1] PROGMEM = { 19 };
const unsigned char endIndices[20] PROGMEM = { 0, 2, 1, 2, 3, 2, 0, 0, 2, 2, 0, 1, 3, 2, 2, 0, 0, 1, 2, 0 };

/*
 * Lists of shortest paths towards drop-off location.
 * Some paths are identical for different starting positions.
 * Drives towards the closest node betweem 4 and 14.
 * 
 * Stored in flash memory.
 */
/*
const unsigned char from_1_a[3] PROGMEM = {2, 3, 4};
const unsigned char from_1_b[3] PROGMEM = {2, 5, 4};
const unsigned char from_2_a[2] PROGMEM = {3, 4};
const unsigned char from_2_b[2] PROGMEM = {5, 4};
const unsigned char from_3_5_a[1] PROGMEM = {4};
const unsigned char from_3_b[3] PROGMEM = {2, 5, 4};
const unsigned char from_5_b[3] PROGMEM = {2, 3, 4};
const unsigned char from_6_9_a[2] PROGMEM = {5, 4};
const unsigned char from_6_9_b[4] PROGMEM = {5, 2, 3, 4};
const unsigned char from_7_8_a[3] PROGMEM = {6, 5, 4};
const unsigned char from_7_8_b[5] PROGMEM = {6, 5, 2, 3, 4};
const unsigned char from_10_a[3] PROGMEM = {9, 5, 4};
const unsigned char from_10_b[3] PROGMEM = {12, 13, 14};
const unsigned char from_11_a[4] PROGMEM = {10, 9, 5, 4};
const unsigned char from_11_b[4] PROGMEM = {10, 12, 13, 14};
const unsigned char from_12_15_a[2] PROGMEM = {13, 14};
const unsigned char from_12_15_b[4] PROGMEM = {13, 19, 18, 14};
const unsigned char from_13_18_a[1] PROGMEM = {14};
const unsigned char from_13_b[3] PROGMEM = {19, 18, 14};
const unsigned char from_18_b[3] PROGMEM = {19, 13, 14};
const unsigned char from_16_17_a[3] PROGMEM = {15, 13, 14};
const unsigned char from_16_17_b[5] PROGMEM = {15, 13, 19, 18, 14};
const unsigned char from_19_a[2] PROGMEM = {18, 14};
const unsigned char from_19_b[2] PROGMEM = {13, 14};
const unsigned char from_20_a[3] PROGMEM = {19, 18, 14};
const unsigned char from_20_b[3] PROGMEM = {19, 13, 14};
*/

#endif
