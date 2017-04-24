#pragma once

#include "Material.h"
#include "Ray.h"
#include <iostream>

class Sphere
{
public:
	Sphere();
	Sphere(glm::vec3 pos, float r);
	bool intersect(const Ray &ray, Intersection &hit);
	~Sphere();
private:
glm::vec3 center;
float radius;

};

