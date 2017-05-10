////////////////////////////////////////
// LambertMaterial.h
////////////////////////////////////////

#pragma once

#include "Material.h"

////////////////////////////////////////////////////////////////////////////////

class LambertMaterial: public Material {
public:
	LambertMaterial();
	~LambertMaterial();
	void computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit);
	void generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor);
private:
	Color diffuseColor;
};

////////////////////////////////////////////////////////////////////////////////
