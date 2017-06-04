#pragma once
#include "Material.h"
class PureFresnelMaterial: public Material
{
public:
	PureFresnelMaterial();
	~PureFresnelMaterial();
	void computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit);
	void generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor);
	void generateReflectedSample(const Intersection isect, const glm::vec3 inDir, glm::vec3 &outDir);
	void generateRefractedSample(const Intersection isect, const glm::vec3 inDir, glm::vec3 &outDir);
	float getRefractedLightProp(const Intersection isect, const glm::vec3 inDir, const glm::vec3 outDir);
	void setRefractiveIndex(float n);
private:
	float n;
	float ni, nt;
	float fr;

};

