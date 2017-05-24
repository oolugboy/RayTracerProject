#pragma once
#include "Material.h"
class AshikhminMaterial : public Material
{
public:
	AshikhminMaterial();
	~AshikhminMaterial();
	void computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit);
	void generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor);
	float getShlickApprox(float kDotH);
	float getSpecularReflectance(const Intersection &isect, const glm::vec3 &inDir, const glm::vec3 &outDir);
	float getDiffuseReflectance(const Intersection & isect, const glm::vec3 & inDir, const glm::vec3 & outDir);
	glm::vec3 getCartesianVector(const Intersection isect, float theta, float phi);
	void generateDiffuseSample(const Intersection isect, const glm::vec3 inDir, glm::vec3 & outDir);
	float generateSpecularSample(const Intersection isect, const glm::vec3 inDir, glm::vec3 & outDir);
	float getSpecularProbability(glm::vec3 normal, glm::vec3 h, float phi);
	float getPhi(float eps1);
	float getTheta(float eps2, float phi);
	static void seedRandomGenerator(int seed);
};

