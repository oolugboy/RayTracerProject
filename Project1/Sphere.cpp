#include "Sphere.h"


Sphere::Sphere()
{
	this->center = glm::vec3(0);
	this->radius = 0.0f;
}
Sphere::Sphere(glm::vec3 pos, float r)
{
	this->center = pos;
	this->radius = r;
}
bool Sphere::intersect(const Ray &ray, Intersection &hit)
{
	glm::vec3 q = ray.origin - (glm::dot((ray.origin - center), ray.direction) * ray.direction);
	float qDist = glm::distance(center, q);
	if (qDist <= radius)
	{
		float a = sqrt(pow(radius, 2) - pow(qDist, 2));
		float t = glm::dot(-1.0f * (ray.origin - center), ray.direction);
		if (t - a >= 0)
		{
			hit.dist = (t - a);
			hit.position = ray.origin + (hit.dist * ray.direction);
			hit.normal = glm::normalize(hit.position - center);	
			return true;
		}
		else // Assume not possible
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
Sphere::~Sphere()
{
}
