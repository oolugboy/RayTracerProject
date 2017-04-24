////////////////////////////////////////
// Triangle.h
////////////////////////////////////////

#pragma once

#include "Vertex.h"
#include "Material.h"
#include "Ray.h"
#include <iostream>

using namespace std;


////////////////////////////////////////////////////////////////////////////////

class Triangle {
public:
	Triangle();
	void init(Vertex *v0, Vertex *v1, Vertex *v2, Material *m)		
	{
		vertices[0]=v0; 
		vertices[1]=v1; 
		vertices[2]=v2; 
		mtl = m;
		xAxis = yAxis = zAxis = false;
	}

	bool intersect(const Ray &ray, Intersection &hit) const;
	bool xAxis, yAxis, zAxis;
	glm::vec3 center;

	Vertex * getVtx(int index);

	void printVector(glm::vec3 val)
	{
		cout << val.x << " " << val.y << " " << val.z << endl;
	}
private:
	Vertex * vertices[3];
	Material * mtl;

};

////////////////////////////////////////////////////////////////////////////////
