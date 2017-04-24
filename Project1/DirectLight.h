#pragma once
#include "Light.h"
class DirectLight :	public Light
{
public:
	DirectLight();
	~DirectLight();
	float illuminate(const glm::vec3 & pos, Color & col, glm::vec3 & toLight, glm::vec3 & ltPos, glm::vec3 normal);
	void setDirection(glm::vec3 & dir);
private:
	glm::vec3 direction;
};

