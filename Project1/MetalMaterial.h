#pragma once
#include "Material.h"
class MetalMaterial :	public Material
{
public:
	MetalMaterial();
	~MetalMaterial();
	void generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor);
	void computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit);
};

