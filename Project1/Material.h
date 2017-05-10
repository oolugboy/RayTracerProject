////////////////////////////////////////
// Material.h
////////////////////////////////////////

#pragma once

#include "Intersection.h"

////////////////////////////////////////////////////////////////////////////////

class Material {
public:
	virtual void computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit)=0;
	virtual void generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor) = 0;
	Color diffuseColor;
	void setColor(Color val);
	bool isDielectric;
};

////////////////////////////////////////////////////////////////////////////////
