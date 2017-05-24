#include "InstanceObject.h"
#include "Util.h"
#include <iostream>


InstanceObject::InstanceObject()
{
}

bool InstanceObject::intersect(const Ray & ray, Intersection & hit)
{
	Ray ray2;
	ray2.origin = glm::vec3(inverse * glm::vec4(ray.origin, 1));
	ray2.direction = glm::vec3(inverse * glm::vec4(ray.direction, 0));
	
	if (child->intersect(ray2, hit) == false)
		return false; 
	hit.position = glm::vec3(matrix * glm::vec4(hit.position, 1));
	hit.normal = glm::vec3(matrix * glm::vec4(hit.normal, 0));
	hit.dist = glm::distance(ray.origin, hit.position); // Correct for any scaling
	if (this->mtl)
	{
		hit.mtl = this->mtl;
	}
	return true;
}
bool InstanceObject::closestIntersect(const Ray & ray, Intersection & hit)
{
	if (ray.debug)
	{
		cout << " Ray dir ";
		printVector(ray.direction);
	}

	Ray ray2;
	ray2.origin = glm::vec3(inverse * glm::vec4(ray.origin, 1));
	ray2.direction = glm::vec3(inverse * glm::vec4(ray.direction, 0));

	if (child->closestIntersect(ray2, hit) == false)
		return false;

	hit.position = glm::vec3(matrix * glm::vec4(hit.position, 1));
	hit.normal = glm::normalize(glm::vec3(matrix * glm::vec4(hit.normal, 0)));
	hit.tangentU = glm::normalize(glm::vec3(matrix * glm::vec4(hit.tangentU, 0.0f)));
	hit.tangentV = glm::normalize(glm::vec3(matrix * glm::vec4(hit.tangentV, 0.0f)));
	hit.dist = glm::distance(ray.origin, hit.position); // Correct for any scaling

	if (this->mtl)
	{
		hit.mtl = this->mtl;
	}
	return true;
}
void InstanceObject::setMaterial(Material * mtl)
{
	this->mtl = mtl;
}
void InstanceObject::setChild(Object &obj)
{
	child = &(obj);
}
void InstanceObject::setMatrix(glm::mat4x4 &mtx)
{
	matrix = mtx;
	inverse = glm::inverse(matrix);
}
InstanceObject::~InstanceObject()
{
}
