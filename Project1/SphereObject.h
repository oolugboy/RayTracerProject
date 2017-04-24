#pragma once
#include "Object.h"
#include "Sphere.h"
class SphereObject : public Object
{
public:
	SphereObject(glm::vec3 pos, float r);	
	~SphereObject();

	void setRadius(float r)
	{ 
		this->radius = r;
	}
	void setCenter(glm::vec3 pos)
	{
		this->center = pos;
	}
	bool SphereObject::intersect(const Ray &ray, Intersection &hit);
	bool SphereObject::closestIntersect(const Ray &ray, Intersection &hit);
private:
	float radius;
	glm::vec3 center;
	Sphere sphere;
};

