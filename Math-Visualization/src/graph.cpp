#include "../headers/graph.h"

Graph::Graph(float iX, float xX, float iY, float xY, int s) {
	size = s;
	minX = iX;
	maxX = xX;
	resX = (maxX - minX) / size;
	minY = iY;
	maxY = xY;
	resY = (maxY - minY) / size;
	t = 0;
	calculateF();
}

void Graph::printGraph(void) {
	int i, j;
	for (i = 0; i <= size; i++) {
		for (j = 0; j <= size; j++) {
			printf("(%f,%f,%f) ", minX + i * resX, minY + j * resY, f[i][j]);
		}
		printf("\n");
	}
}

void Graph::calculateF() {
	int i, j;
	for (i = 0; i <= size; i++) {
		std::vector<float> two;
		f.push_back(two);
		for (j = 0; j <= size; j++) {
			f[i].push_back(mathFunction(minX + i * resX, minY + j * resY));
		}
	}
}

void Graph::updateF() {
	int i, j;
	t += 0.01;
	for (i = 0; i <= size; i++) {
		for (j = 0; j <= size; j++) {
			f[i][j] = mathFunction(minX + i * resX, minY + j * resY);
		}
	}
}

float Graph::mathFunction(float x, float y) {
	return cos(x - t) * sin(y - t);
}