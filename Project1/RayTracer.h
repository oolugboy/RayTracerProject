#pragma once
#include "Color.h"
#include "Scene.h"

class RayTracer
{
public:
	RayTracer();
	void rayTrace(Ray & ray, Scene & s, Color & pixelColor);
	void getDirectLight(Ray & ray, Scene & s, Color & pixelColor);
	~RayTracer();
};

