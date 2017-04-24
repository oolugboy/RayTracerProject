////////////////////////////////////////
// MeshObject.cpp
////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include "MeshObject.h"
#include "LambertMaterial.h"
#include "glm/glm.hpp"

////////////////////////////////////////////////////////////////////////////////

MeshObject::MeshObject() {
	numVertices=0;
	numTriangles=0;
	vertices=0;
	triangles=0;
}

////////////////////////////////////////////////////////////////////////////////

MeshObject::~MeshObject() {
	delete [] vertices;
	delete [] triangles;
}

////////////////////////////////////////////////////////////////////////////////

bool MeshObject::intersect(const Ray &ray, Intersection &hit) {
	bool success=false;
	for(int i=0; i<numTriangles; i++)
		if(triangles[i].intersect(ray,hit)) success=true;
	return success;
}

int MeshObject::getNumTriangles()
{
	return numTriangles;
}
Triangle * MeshObject::getTrianglesPointer()
{
	return triangles;
}
bool MeshObject::closestIntersect(const Ray & ray, Intersection & hit)
{
	if (ray.debug)
	{
		cout << " The origin of the ray ";
		printVector(ray.origin);
		cout << " The num Triangles is " << numTriangles << endl;
	}
	bool success = false;
	Intersection closestHit = Intersection();

	for (int i = 0; i < numTriangles; i++)
	{
		
		if (triangles[i].intersect(ray, hit))
		{
			success = true;
			if (hit.dist < closestHit.dist)
			{
				closestHit = hit;
			}
		}
	}

	hit = closestHit;
	return success;
}
////////////////////////////////////////////////////////////////////////////////

void MeshObject::makeBox(float x,float y,float z,Material *mtl) {
	// Allocate arrays
	numVertices=24;
	numTriangles=12;
	vertices=new Vertex[numVertices];
	triangles=new Triangle[numTriangles];
	if(mtl==0) mtl=new LambertMaterial;

	x*=0.5f;
	y*=0.5f;
	z*=0.5f;

	// Corners
	glm::vec3 p000(-x,-y,-z);
	glm::vec3 p001(-x,-y,z);
	glm::vec3 p010(-x,y,-z);
	glm::vec3 p011(-x,y,z);
	glm::vec3 p100(x,-y,-z);
	glm::vec3 p101(x,-y,z);
	glm::vec3 p110(x,y,-z);
	glm::vec3 p111(x,y,z);

	// Tex coords
	glm::vec3 t00(0.0f,0.0f,0.0f);
	glm::vec3 t01(0.0f,1.0f,0.0f);
	glm::vec3 t10(1.0f,0.0f,0.0f);
	glm::vec3 t11(1.0f,1.0f,0.0f);

	// Axis vectors
	glm::vec3 xAxis(1,0,0);
	glm::vec3 yAxis(0,1,0);
	glm::vec3 zAxis(0,0,1);

	// Right
	vertices[0].set(p101,xAxis,t00);
	vertices[1].set(p100,xAxis,t10);
	vertices[2].set(p110,xAxis,t11);
	vertices[3].set(p111,xAxis,t01);
	triangles[0].init(&vertices[0],&vertices[1],&vertices[2],mtl);
	triangles[1].init(&vertices[0],&vertices[2],&vertices[3],mtl);

	// Left
	vertices[4].set(p000,-xAxis,t00);
	vertices[5].set(p001,-xAxis,t10);
	vertices[6].set(p011,-xAxis,t11);
	vertices[7].set(p010,-xAxis,t01);
	triangles[2].init(&vertices[4],&vertices[5],&vertices[6],mtl);
	triangles[3].init(&vertices[4],&vertices[6],&vertices[7],mtl);

	// Top
	vertices[8].set(p011,yAxis,t00);
	vertices[9].set(p111,yAxis,t10);
	vertices[10].set(p110,yAxis,t11);
	vertices[11].set(p010,yAxis,t01);
	triangles[4].init(&vertices[8],&vertices[9],&vertices[10],mtl);
	triangles[5].init(&vertices[8],&vertices[10],&vertices[11],mtl);

	// Bottom
	vertices[12].set(p000,-yAxis,t00);
	vertices[13].set(p100,-yAxis,t10);
	vertices[14].set(p101,-yAxis,t11);
	vertices[15].set(p001,-yAxis,t01);
	triangles[6].init(&vertices[12],&vertices[13],&vertices[14],mtl);
	triangles[7].init(&vertices[12],&vertices[14],&vertices[15],mtl);

	// Front
	vertices[16].set(p001,zAxis,t00);
	vertices[17].set(p101,zAxis,t10);
	vertices[18].set(p111,zAxis,t11);
	vertices[19].set(p011,zAxis,t01);
	triangles[8].init(&vertices[16],&vertices[17],&vertices[18],mtl);
	triangles[9].init(&vertices[16],&vertices[18],&vertices[19],mtl);

	// Back
	vertices[20].set(p100,-zAxis,t00);
	vertices[21].set(p000,-zAxis,t10);
	vertices[22].set(p010,-zAxis,t11);
	vertices[23].set(p110,-zAxis,t01);
	triangles[10].init(&vertices[20],&vertices[21],&vertices[22],mtl);
	triangles[11].init(&vertices[20],&vertices[22],&vertices[23],mtl);
}

bool MeshObject::loadPLY(const char *filename, Material *mtl)
{
	// Open file
	FILE *f = fopen(filename, "r");
	if (f == 0) {
		printf("ERROR: MeshObject::LoadPLY()- Can't open '%s'\n", filename);
		return false;
	}
	// Read header
	char tmp[256];
	int numverts = 0, numtris = 0;
	int posprop = -99, normprop = -99;
	int props = 0;
	while (1) {
		fgets(tmp, 256, f);
		if (strncmp(tmp, "element vertex", 14) == 0)
		{			
			numverts = atoi(&tmp[14]);
		}
		if (strncmp(tmp, "element face", 12) == 0)
		{			
			numtris = atoi(&tmp[12]);
		}
		if (strncmp(tmp, "property", 8) == 0)
		{			
			int len = strlen(tmp);
			if (strncmp(&tmp[len - 3], " x", 2) == 0) posprop = props;
			if (strncmp(&tmp[len - 3], "nx", 2) == 0) normprop = props;
			props++;
		}
		if (strcmp(tmp, "end_header\n") == 0)
		{			
			break;
		}
	}
	
	if (posprop == -1) {
		printf("ERROR: MeshObject::LoadPLY()- No vertex positions found\n");
		fclose(f);
		return false;
	}
	// Read verts
	int i = 0;
	if (numverts>0) {
		numVertices = numverts;
		vertices = new Vertex[numVertices];
		for (i = 0; i< numVertices; i++) {
			fgets(tmp, 256, f);
			char *pch = strtok(tmp, " ");
			int prop = 0;
			while (pch) {
				if (prop == posprop) vertices[i].position.x = float(atof(pch));
				if (prop == posprop + 1) vertices[i].position.y = float(atof(pch));
				if (prop == posprop + 2) vertices[i].position.z = float(atof(pch));
				if (prop == normprop) vertices[i].normal.x = float(atof(pch));
				if (prop == normprop + 1) vertices[i].normal.y = float(atof(pch));
				if (prop == normprop + 2) vertices[i].normal.z = float(atof(pch));
				pch = strtok(0, " ");
				prop++;
			}
		}
	}
	// Read tris
	if (numtris>0) {
		if (mtl == 0) mtl = new LambertMaterial;
		numTriangles = numtris;
		triangles = new Triangle[numtris];
		for (i = 0; i<numtris; i++) {
			int count, i0, i1, i2;
			fscanf(f, "%d %d %d %d\n", &count, &i0, &i1, &i2);
			if (count != 3) {
				printf("ERROR: MeshObject::LoadPLY()- Only triangles are supported\n");
					fclose(f);
				return false;
			}
			triangles[i].init(&vertices[i0], &vertices[i1], &vertices[i2], mtl);
		}
	}
	// Smooth
	if (normprop<0) smooth();
	// Close file
	fclose(f);
	printf("Loaded %d triangles from file '%s'\n", numtris, filename);
	return true;
}

void MeshObject::smooth() {
	int i, j;
	for (i = 0; i < numVertices; i++)
		vertices[i].normal = glm::vec3(0);
	for (i = 0; i < numTriangles; i++) {
		Triangle &tri = triangles[i];
		glm::vec3 e1 = tri.getVtx(1)->position - tri.getVtx(0)->position;
		glm::vec3 e2 = tri.getVtx(2)->position - tri.getVtx(0)->position;
		glm::vec3 cross = glm::cross(e1, e2);
		for (j = 0; j<3; j++)
			tri.getVtx(j)->normal += cross;
	}
	for (i = 0; i < numVertices; i++)
		vertices[i].normal = glm::normalize(vertices[i].normal);
}
////////////////////////////////////////////////////////////////////////////////
