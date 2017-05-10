#pragma once
#include "Object.h"

using namespace std;

class InstanceObject :	public Object
{
public:
	InstanceObject();
	bool intersect(const Ray &ray, Intersection &hit);
	bool closestIntersect(const Ray & ray, Intersection & hit);	
	void setChild(Object &obj);
	void setMatrix(glm::mat4x4 &mtx);
	void setMaterial(Material * mtl);
	~InstanceObject();
private:
	glm::mat4x4 matrix;
	glm::mat4x4 inverse; // Pre-computed inverse of Matrix
	Object * child;
	Material * mtl;
};

