#pragma once
#include "Material.h"
class AshikhminMaterial : public Material
{
public:
	AshikhminMaterial();
	~AshikhminMaterial();
	void computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit);
	void generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor);
	Color getShlickApprox(float kDotH);
	Color getSpecularReflectance(const Intersection &isect, const glm::vec3 &inDir, const glm::vec3 &outDir);
	Color getDiffuseReflectance(const Intersection & isect, const glm::vec3 & inDir, const glm::vec3 & outDir);
};

