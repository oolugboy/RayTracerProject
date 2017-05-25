#include "LambertMaterial.h"
#include <iostream>

using namespace std;
LambertMaterial::LambertMaterial()
{
	isLambertian = true;
	isDielectric = false;
	debug = false;
	step = 0;
}
LambertMaterial::~LambertMaterial()
{

}
void LambertMaterial::orientAxis(glm::vec3 & xAxis, glm::vec3 & yAxis, glm::vec3 & zAxis, glm::vec3 normal)
{
	yAxis = normal;
	if (glm::dot(normal, glm::vec3(0.0f, 1.0f, 1.0f)) < 0.9998f)
	{
		xAxis = glm::cross(normal, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	zAxis = glm::cross(xAxis, yAxis);
}
void LambertMaterial::generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor)
{
	glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f), yAxis = glm::vec3(0.0f, 1.0f, 0.0f), zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	orientAxis(xAxis, yAxis, zAxis, isect.normal);

	float s = (float)rand() / RAND_MAX;
	float t = (float)rand() / RAND_MAX;

	float PI = 3.1415926f;
	float u = 2 * PI * s;
	float v = sqrt(1 - t);

	outDir = (v * cos(u) * xAxis) + (sqrt(t) * yAxis) + (v * sin(u) * zAxis);
	outColor = Color(1.0f);
}
void LambertMaterial::seedRandomGenerator(int seed)
{
	srand(seed);
}
void LambertMaterial::computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit) {
	float pi = 3.1415926f;
	Color temp;
	temp.scale(diffuseColor, 1.0f / pi);
	col.multiply(temp);
	col.scale(pi);
}