#include "PlaneObject.h"



PlaneObject::PlaneObject(glm::vec3 position, glm::vec3 normal)
{
	plane = Plane(position, normal);
}
PlaneObject::PlaneObject()
{}
bool PlaneObject::intersect(const Ray &ray, Intersection &hit)
{
	return plane.intersect(ray, hit);
}
bool PlaneObject::closestIntersect(const Ray & ray, Intersection & hit)
{
	return intersect(ray, hit);
}
PlaneObject::~PlaneObject()
{
}

bool intersect(const Ray &ray, Intersection &hit);
bool closestIntersect(const Ray & ray, Intersection & hit);