#include "graph.h"

/*
* Get weight of node with respect to current node.
*/
const uint8_t getWeight(uint8_t currentNode, uint8_t adjacentNode) {
	return weightMatrix[currentNode - 1][adjacentNode - 1];
}

/*
* Returns array of adjacent nodes.
*/
const uint8_t * getAdjacent(uint8_t node) {
	switch (node) {
	case 1:
		return adj_1;
	case 2:
		return adj_2;
	case 3:
		return adj_3;
	case 4:
		return adj_4;
	case 5:
		return adj_5;
	case 6:
		return adj_6;
	case 7:
		return adj_7;
	case 8:
		return adj_8;
	case 9:
		return adj_9;
	case 10:
		return adj_10;
	case 11:
		return adj_11;
	case 12:
		return adj_12;
	case 13:
		return adj_13;
	case 14:
		return adj_14;
	case 15:
		return adj_15;
	case 16:
		return adj_16;
	case 17:
		return adj_17;
	case 18:
		return adj_18;
	case 19:
		return adj_19;
	case 20:
		return adj_20;
	}
}