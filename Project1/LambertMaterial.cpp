#include "LambertMaterial.h"

LambertMaterial::LambertMaterial()
{

}
LambertMaterial::~LambertMaterial()
{

}
void LambertMaterial::generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor)
{

}
void LambertMaterial::computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit) {
	float pi = 3.1415926f;
	Color temp;
	temp.scale(diffuseColor, 1.0f / pi);
	col.multiply(temp);
	col.scale(3.2f);
}