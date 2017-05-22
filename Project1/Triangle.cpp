#include "Triangle.h"

Triangle::Triangle()
{

}

Vertex * Triangle::getVtx(int index)
{
	return vertices[index];
}
bool Triangle::intersect(const Ray & ray, Intersection & hit) const
{
	//cout << " In triangle intersect " << endl;
	glm::vec3 a = vertices[0]->position;
	glm::vec3 b = vertices[1]->position;
	glm::vec3 c = vertices[2]->position;
	if (ray.debug)
	{
		cout << " The vertices " << endl;	
		cout << a.x << " " << a.y << " " << a.z << endl;
		cout << b.x << " " << b.y << " " << b.z << endl;
		cout << c.x << " " << c.y << " " << c.z << endl;
	}
	float detM = glm::dot((-1.0f * ray.direction), glm::cross(b - a, c - a));
	if (detM == 0) // Parallel to surface 
	{
		return false;
	}
	hit.dist = glm::dot(ray.origin - a, glm::cross(b - a, c - a))/detM;

	float alpha = glm::dot(-1.0f * ray.direction, glm::cross(ray.origin - a, c - a))/detM;
	float beta = glm::dot(-1.0f * ray.direction, glm::cross(b - a, ray.origin - a))/detM;

	if (alpha > 0.0f && beta > 0.0f && (alpha + beta) < 1 && hit.dist > 0.001f)
	{
		hit.normal = glm::normalize((1 - alpha - beta) * vertices[0]->normal + (alpha * vertices[1]->normal) + (beta * vertices[2]->normal));	
		if (glm::dot(ray.direction, hit.normal) > 0)
		{
			hit.normal = hit.normal * -1.0f;
		}
		hit.mtl = this->mtl;
		hit.position = ray.origin + (hit.dist * ray.direction);

		/* Compute the tangent vectors */
		hit.tangentU = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), hit.normal);
		if (glm::length(hit.tangentU) < 0.001f)
		{
			hit.tangentU = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), hit.normal);
		}
		hit.tangentU = glm::normalize(hit.tangentU);
		hit.tangentV = glm::cross(hit.normal, hit.tangentU);
		return true;
	}
	else
	{
		return false;
	}	
}