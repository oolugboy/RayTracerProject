#include "Plane.h"

Plane::Plane(glm::vec3 position, glm::vec3 normal)
{
	this->position = position;
	this->normal = normal;
}
Plane::Plane()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->normal = glm::vec3(0.0f, 1.0f, 0.0f);
}
bool Plane::intersect(const Ray & ray, Intersection & hit)
{
	float d = glm::dot(normal, position);
	float tNum = (d - glm::dot(ray.origin, normal));
	float tDenum = glm::dot(ray.direction, normal);	
	if(tDenum == 0)
		return false;
	else
	{
		float t = tNum / tDenum;
		if (t >= 0.001f)
		{
			hit.dist = t;
			hit.position = ray.origin + (hit.dist * ray.direction);
			hit.normal = this->normal;
			return true;
		}
		else
			return false;
	}
}

Plane::~Plane()
{
}
