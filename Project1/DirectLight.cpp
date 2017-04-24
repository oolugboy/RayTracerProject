#include "DirectLight.h"



DirectLight::DirectLight()
{
	
}

float DirectLight::illuminate(const glm::vec3 & pos, Color & col, glm::vec3 & toLight, glm::vec3 & ltPos, glm::vec3 normal)
{
	toLight = -1.0f * direction;
	col = baseColor;
	ltPos = pos - (1000000.0f * direction); // Create virtual position
	return (intensity * fmax(0.0f, glm::dot(toLight, normal)));
}
void DirectLight::setDirection(glm::vec3 & dir)
{
	direction = glm::normalize(dir);
}

DirectLight::~DirectLight()
{
}
