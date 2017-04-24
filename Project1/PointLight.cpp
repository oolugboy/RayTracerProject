#include "PointLight.h"
#include < iostream>

PointLight::PointLight()
{
	
}

float PointLight::illuminate(const glm::vec3 & pos, Color & col, glm::vec3 & toLight, glm::vec3 & ltPos, glm::vec3 normal)
{
	toLight = position - pos;
	float normScale = fmax(0.0f, glm::dot(glm::normalize(toLight), normal));

	float bright = (intensity / (pow(glm::length(toLight), 2.0f))) * normScale; // Inverse square falloff	
	toLight = glm::normalize(toLight);
	col = baseColor;
	ltPos = position;	
	return bright;
}
void PointLight::setPosition(glm::vec3 pos)
{
	position = pos;
}
PointLight::~PointLight()
{

}
