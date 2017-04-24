////////////////////////////////////////
// Light.h
////////////////////////////////////////

#pragma once

#include "Color.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class Light {
public:
	Light()									{intensity=1.0; baseColor=Color::WHITE;}
	void setBaseColor(const Color &col)		
	{
		baseColor=col;		
	}
	void setIntensity(float i)				
	{
		intensity=i;
	}
	void printVector(glm::vec3 val)
	{
		cout << val.x << " " << val.y << " " << val.z << endl;
	}

	virtual float illuminate(const glm::vec3 &pos, Color &col, glm::vec3 &toLight, glm::vec3 &ltPos, glm::vec3 normal)=0;

protected:
	float intensity;
	Color baseColor;		// Actual color is Intensity*BaseColor
	
};

////////////////////////////////////////////////////////////////////////////////
