////////////////////////////////////////
// MeshObject.h
////////////////////////////////////////

#pragma once

#include "Object.h"
#include "Triangle.h"

////////////////////////////////////////////////////////////////////////////////

class MeshObject:public Object {
public:
	MeshObject();
	~MeshObject();

	bool intersect(const Ray &ray,Intersection &hit);
	bool closestIntersect(const Ray & ray, Intersection & hit);

	void makeBox(float x, float y,float z, Material *mtl=0);
	 
	bool loadPLY(const char * filename, Material * mtl);

	void smooth();

	int getNumTriangles();

	Triangle * getTrianglesPointer();

private:
	int numVertices, numTriangles;
	Vertex * vertices;
	Triangle * triangles;
};

////////////////////////////////////////////////////////////////////////////////
