////////////////////////////////////////
// LambertMaterial.h
////////////////////////////////////////

#pragma once

#include "Material.h"

////////////////////////////////////////////////////////////////////////////////

class LambertMaterial:public Material {
public:
	void computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit) {
		float pi=3.1415926f;
		Color temp;
		temp.scale(diffuseColor,1.0f/pi);
		col.multiply(temp);
		col.scale(3.2f);
	}

private:
	Color diffuseColor;
};

////////////////////////////////////////////////////////////////////////////////
