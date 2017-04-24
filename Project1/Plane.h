#pragma once

#include "Plane.h"
#include "Vertex.h"
#include "Material.h"
#include "Ray.h"
#include <iostream>

class Plane
{
public:
	Plane();
	Plane(glm::vec3 position, glm::vec3 normal);
	~Plane();
	bool intersect(const Ray & ray, Intersection & hit);
private:
	glm::vec3 position;
	glm::vec3 normal;
};

