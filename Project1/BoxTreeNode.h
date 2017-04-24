#pragma once
#include "Ray.h"
#include "Intersection.h"
#include "Triangle.h"  
#include <time.h>
#include <vector> 
#include <algorithm>

class BoxTreeNode
{
public:
	BoxTreeNode();
	~BoxTreeNode();
	bool intersect(const Ray & ray, Intersection & hit);
	bool closestIntersect(const Ray & ray, Intersection & hit);
	void fillBoxDimensions(int count, Triangle * tri);
	void getLargestAxis(bool & xAxis, bool & yAxis, bool & zAxis);
	bool boxIntersect(const Ray & ray, Intersection & hit);
	void construct(int count, Triangle * tri);
	pair<int, int> groupTriangles(int count, Triangle * tri1, Triangle * tri2, Triangle * tri);
	void printVector(glm::vec3 val);
	static int rCounter;	
private:
	bool xAxis, yAxis, zAxis;
	const int maxTriangleNum = 2;
	glm::vec3 boxMin, boxMax;
	BoxTreeNode * child1, * child2;
	float maxX, maxY, maxZ;
	float minX, minY, minZ;
	float numTriangles;
	Triangle triangles[5];

};

