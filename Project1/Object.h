////////////////////////////////////////
// Object.h
////////////////////////////////////////

#pragma once

#include "Ray.h"
#include "Intersection.h"
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class Object {
public:
	virtual ~Object()	{}
	virtual bool intersect(const Ray &ray, Intersection &hit)=0;
	virtual bool closestIntersect(const Ray & ray, Intersection & hit) = 0;
	void printVector(glm::vec3 val)
	{
		cout << val.x << " " << val.y << " " << val.z << endl;
	}
};

////////////////////////////////////////////////////////////////////////////////
