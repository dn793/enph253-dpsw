#include "Navigation.h"

List * createList(unsigned char capacity)
{
	List *l;
	l = (List *)malloc(sizeof(List));
	
	l->list = (unsigned char *)malloc(sizeof(unsigned char) * capacity);
	l->size	= 0;
	l->front = 0;
	l->rear	= -1;

	return l;
}

unsigned char pop(List *l)
{
	--l->size;
	unsigned char node = l->list[l->front++];
	return node;
}

void enqueue(List *l, unsigned char node)
{
	++l->size;
	l->rear = l->rear + 1;
	l->list[l->rear] = node;
	return;
}

void push(List *l, unsigned char node)
{
    unsigned char i;
    
	++l->size;
	l->rear = l->rear + 1;
	for (i = 0; i < l->size + 1; ++i) { l->list[l->rear - i] = l->list[l->rear - i - 1]; }
	l->list[l->front] = node;
	return;
}

unsigned char getWeight(unsigned char currentNode, unsigned char adjacentNode) 
{	return (unsigned char)weightMatrix[currentNode - 1][adjacentNode - 1]; }

unsigned char * getAdjacent(unsigned char node)
{
	switch (node) {
		case 1: return (unsigned char *)adj_1;
		case 2: return (unsigned char *)adj_2;
		case 3: return (unsigned char *)adj_3;
		case 4: return (unsigned char *)adj_4;
		case 5: return (unsigned char *)adj_5;
		case 6: return (unsigned char *)adj_6;
		case 7: return (unsigned char *)adj_7;
		case 8: return (unsigned char *)adj_8;
		case 9: return (unsigned char *)adj_9;
		case 10: return (unsigned char *)adj_10;
		case 11: return (unsigned char *)adj_11;
		case 12: return (unsigned char *)adj_12;
		case 13: return (unsigned char *)adj_13;
		case 14: return (unsigned char *)adj_14;
		case 15: return (unsigned char *)adj_15;
		case 16: return (unsigned char *)adj_16;
		case 17: return (unsigned char *)adj_17;
		case 18: return (unsigned char *)adj_18;
		case 19: return (unsigned char *)adj_19;
		case 20: return (unsigned char *)adj_20;
	}
}

unsigned char * getDropOffPath(unsigned char node)
{
	switch (node) {
		case 1: return (unsigned char *)from_1_a;
		case 2: return (unsigned char *)from_2_a;
		case 3: return (unsigned char *)from_3_5_a;
		case 5: return (unsigned char *)from_3_5_a;
		case 6: return (unsigned char *)from_6_9_a;
		case 7: return (unsigned char *)from_7_8_a;
		case 8: return (unsigned char *)from_7_8_a;
		case 9: return (unsigned char *)from_6_9_a;
		case 10: return (unsigned char *)from_10_a;
		case 11: return (unsigned char *)from_11_a;
		case 12: return (unsigned char *)from_12_15_a;
		case 13: return (unsigned char *)from_13_18_a;
		case 15: return (unsigned char *)from_12_15_a;
		case 16: return (unsigned char *)from_16_17_a;
		case 17: return (unsigned char *)from_16_17_a;
		case 18: return (unsigned char *)from_13_18_a;
		case 19: return (unsigned char *)from_19_a;
		case 20: return (unsigned char *)from_20_a;
	}
}

//Queue * shortestPath(unsigned char initialNode, unsigned char finalNode) {
//	Queue *path = createQueue(255);
//	unsigned char visited[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//	unsigned char prev[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//
//	unsigned char currentNode = initialNode;
//	unsigned char *adjacents = getAdjacent(currentNode);
//	for (unsigned char i = 0; i < adjSizes[currentNode - 1]; ++i) { enqueue(path, adjacents[i]); }
//	//enqueue(path, adjacents[0]); enqueue(path, adjacents[1]); enqueue(path, adjacents[2]);
//	//enqueue(path, *(adjacents));
//	//enqueue(path, *(adjacents + 1));
//	//enqueue(path, *(adjacents + 2));
//
//	/*prev[*adjacents - 1] = currentNode;
//	for (int i = 1; i < adjSizes[currentNode - 1]; ++i) {
//		enqueue(q, *(adjacents + i));
//		prev[*(adjacents + i) - 1] = currentNode;
//	}*/
//
//	/*while (q->size != 0) {
//		currentNode = pop(q);
//
//		if (visited[currentNode - 1] == 0) {
//			visited[currentNode - 1] = 1;
//
//			const unsigned char *adjacents = getAdjacent(currentNode);
//			enqueue(q, *adjacents);
//			prev[*adjacents - 1] = currentNode;
//			for (int i = 1; i < adjSizes[currentNode - 1]; ++i) {
//				enqueue(q, *(adjacents + i));
//				prev[*(adjacents + i) - 1] = currentNode;
//			}
//		}
//	}
//
//	currentNode = finalNode;
//	while (prev[currentNode - 1] != 0) {
//		enqueue(q, currentNode);
//		currentNode = prev[currentNode - 1];
//	}*/
//
//	return path;
//}