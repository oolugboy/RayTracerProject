////////////////////////////////////////
// Vertex.h
////////////////////////////////////////

#pragma once

#include "glm/glm.hpp"

////////////////////////////////////////////////////////////////////////////////

class Vertex {
public:
	void set(glm::vec3 &p, glm::vec3 &n, glm::vec3 &t)	
	{
		position=p; 
		normal=n; 
		texCoord=t;
	}	
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texCoord;
};

////////////////////////////////////////////////////////////////////////////////
