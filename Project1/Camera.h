////////////////////////////////////////
// Camera.h
////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include "Bitmap.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Scene.h"
#include <iostream>

using namespace std;

class Camera {
public:
	Camera();
	~Camera();
	void setFOV(float f);
	void setAspect(float a);
	void setResolution(int x, int y);
	void lookAt(glm::vec3 & pos, glm::vec3 & target, glm::vec3 & up);
	void render(Scene & s);
	void renderPixel(int x, int y, Scene & s);
	void saveBitmap(char * filename);
	int count;
	void colorPixel(Ray ray, int x, int y, Scene & s);
	void printVector(glm::vec3 val)
	{
		cout << val.x << " " << val.y << " " << val.z << endl;
	}
private:
	int xRes, yRes;
	glm::mat4x4 worldMatrix;
	float verticalFOV;
	float aspect;
	Bitmap * bMP;
};
