////////////////////////////////////////
// Camera.h
////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include "Bitmap.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Scene.h"
#include "RayTracer.h"
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
	void saveBitmap(char * filename);
	int count;
	void setSuperSample(float xSamples, float ySamples);
	void setJitter(bool jitter);
	void setShirley(bool shirley);
	void samplePixel(int x, int y, Scene & s);
	void shootAtPixelOffset(float fx, float fy, Scene &s, Color & pixelColor);
	void superSamplePixel(int x, int y, Scene & s);
	void applyShirley(float & xRand, float & yRand);
	void makeSuperSampler();
	void printVector(glm::vec3 val)
	{
		cout << val.x << " " << val.y << " " << val.z << endl;
	}
private:
	int xRes, yRes;
	glm::mat4x4 worldMatrix;
	float verticalFOV;
	float aspect;
	float xSamples, ySamples;
	bool superSampler;
	bool jitter, shirley;
	Bitmap * bMP;
	RayTracer * rayTracer;
};
