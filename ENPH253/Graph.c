#include "graph.h"

const unsigned char getWeight(unsigned char currentNode, unsigned char adjacentNode) {
	return weightMatrix[currentNode - 1][adjacentNode - 1];
}

const unsigned char * getAdjacent(unsigned char node) {
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

Queue * createQueue() {
	Queue *q;
	q = (Queue *)malloc(sizeof(Queue));
	q->queue = (unsigned char *)malloc(sizeof(unsigned char) * 20);
	q->size = 0;
	q->front = 0;
	q->rear = -1;
	return q;
}

unsigned char pop(Queue *q) {
	unsigned char node = q->queue[q->front++];
	--q->size;
	return node;
}

void enqueue(Queue *q, unsigned char node) {
	++q->size;
	q->rear = q->rear + 1;
	q->queue[q->rear] = node;
	return;
}