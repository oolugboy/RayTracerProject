#include "SphereObject.h"
#include "Sphere.h"



SphereObject::SphereObject(glm::vec3 pos, float r)
{
	this->center = pos;
	this->radius = r;
	sphere = Sphere(pos, r);
}
bool SphereObject::intersect(const Ray &ray, Intersection &hit)
{
	return sphere.intersect(ray, hit);
}
bool SphereObject::closestIntersect(const Ray &ray, Intersection &hit)
{
	return intersect(ray, hit);
}

SphereObject::~SphereObject()
{
}
