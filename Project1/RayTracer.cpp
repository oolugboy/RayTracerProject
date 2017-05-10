#include "RayTracer.h"



RayTracer::RayTracer()
{
}
void RayTracer::rayTrace(Ray & ray, Scene & s, Color & pixelColor)
{
	getDirectLight(ray, s, pixelColor);
}
void RayTracer::getDirectLight(Ray & ray, Scene & s, Color & pixelColor)
{
	Intersection hit = Intersection();

	bool collided = s.getClosestIntersect(ray, hit);

	if (collided)
	{
		vector < Color > colors(s.getNumLights());
		for (int i = 0; i < s.getNumLights(); i++)
		{
			glm::vec3 lightPos;
			glm::vec3 toLight;

			float intensity = s.getLight(i).illuminate(hit.position, colors[i], toLight, lightPos, hit.normal);
			colors[i].scale(intensity);
			Ray shadowRay;
			shadowRay.origin = hit.position;
			shadowRay.direction = glm::normalize(lightPos - hit.position);
			Intersection shadowHit;

			if (s.shadows)
			{
				bool intercept = s.getClosestIntersect(shadowRay, shadowHit);

				if (intercept == false || shadowHit.dist > glm::length(lightPos - hit.position))
				{
					pixelColor.add(colors[i]);
				}
			}
			else
				pixelColor.add(colors[i]);
		}
	}
	else
	{
		pixelColor = s.getSkyColor();
	}
}

RayTracer::~RayTracer()
{
}
