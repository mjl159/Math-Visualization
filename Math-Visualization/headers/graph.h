#ifndef ___GRAPH_H___
#define ___GRAPH_H___

#include "globals.h"

class Graph
{
public:
	std::vector<std::vector<float>> f;
	int size;
	float minX;
	float maxX;
	float resX;
	float minY;
	float maxY;
	float resY;
	float t;

	Graph(float minX, float maxX, float minY, float maxY, int size);

	void calculateF(void);
	void updateF(void);
	void printGraph(void);
private:
	float mathFunction(float x, float y);
};

#endif