#include "MetalMaterial.h"



MetalMaterial::MetalMaterial()
{
	isDielectric = true;	
}
void MetalMaterial::computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit)
{

}
void MetalMaterial::generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor)
{	
	float nDotD = glm::dot(isect.normal, inDir);
	outDir = (2.0f * (nDotD)* isect.normal) - inDir;
	outColor = Color(diffuseColor);
}
MetalMaterial::~MetalMaterial()
{
}
