#pragma once
#include "Light.h"
#include "Color.h"
class PointLight : public Light
{
public:
	PointLight();
	float illuminate(const glm::vec3 & pos, Color & col, glm::vec3 & toLight, glm::vec3 & ltPos, glm::vec3 normal);
	void setPosition(glm::vec3 pos);
	~PointLight();
private:
	glm::vec3 position;
};

