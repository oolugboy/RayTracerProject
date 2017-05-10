#include "MetalMaterial.h"



MetalMaterial::MetalMaterial()
{
	isDielectric = true;
}
void MetalMaterial::computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit)
{
	float nDotD = glm::dot(hit.normal, in);
	glm::vec3 reflOut = (2.0f * (nDotD) * hit.normal) - in;

	if (glm::dot(reflOut, out) > 0.9998f)
	{
		col.multiply(diffuseColor);
	}
	else
	{
		col = Color(0.0f, 0.0f, 0.0f);
	}
}
void MetalMaterial::generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor)
{	
	float nDotD = glm::dot(isect.normal, inDir);
	outDir = (2.0f * (nDotD)* isect.normal) - inDir;
}
MetalMaterial::~MetalMaterial()
{
}
