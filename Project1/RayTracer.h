#pragma once
#include "Color.h"
#include "Scene.h"
#include "Material.h"

class RayTracer
{
public:
	RayTracer();
	void rayTrace(Ray & ray, Scene & s, Color & pixelColor);
	void pathTrace(Ray & ray, Scene & s, Color & pixelColor, int step);
	void getDirectLight(Ray & ray, Scene & s, Intersection & hit,  Color & pixelColor);
	void getDirectLightPath(Ray & ray, Scene & s, Intersection & hit, Color & pixelColor, int step);
	~RayTracer();
private:
	int maxNumSteps;
};

