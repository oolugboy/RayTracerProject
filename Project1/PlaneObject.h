#pragma once
#include "Object.h"
#include "Plane.h"

class PlaneObject : public Object
{
public:
	PlaneObject(glm::vec3 position, glm::vec3 normal);
	PlaneObject();
	~PlaneObject();

	bool intersect(const Ray &ray, Intersection &hit);
	bool closestIntersect(const Ray & ray, Intersection & hit);

private:
	Plane plane;
};

