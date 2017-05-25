#include "RayTracer.h"

RayTracer::RayTracer()
{
	maxNumSteps = 10;
}
void RayTracer::rayTrace(Ray & ray, Scene & s, Color & pixelColor)
{
	Intersection hit = Intersection();
	bool collided = s.getClosestIntersect(ray, hit);

	if (collided)
	{
		getDirectLight(ray, s, hit, pixelColor);		
	}
	else
	{
		pixelColor = s.getSkyColor();
	}
}
void RayTracer::pathTrace(Ray & ray, Scene & s, Color & pixelColor, int step)
{
	if(step > maxNumSteps)
	{
		return;
	}
	else
	{ 
		/* Got the first hit */
		Intersection hit = Intersection();
		bool collided = s.getClosestIntersect(ray, hit);
		
		if (collided)
		{
			if (!(hit.mtl->isDielectric))
			{
				/* Try to get the first light */
				getDirectLightPath(ray, s, hit, pixelColor, step);
			}

			/* now to get the reflected ray diretection */
			glm::vec3 outDir;	
			Color inateReflColor = Color(0.0f);
			hit.mtl->generateSample(hit, -1.0f * ray.direction, outDir, inateReflColor);

			/* Then pathTrace the reflected ray */
			Ray reflRay;
			reflRay.origin = hit.position;
			reflRay.direction = outDir;
				
			Color reflColor = Color(0.0f, 0.0f, 0.0f);
			pathTrace(reflRay, s, reflColor, step + 1);
			if (hit.mtl->isLambertian)
			{
				hit.mtl->computeReflectance(reflColor, reflRay.direction, -1.0f * ray.direction, hit);
			}
			else
			{
				reflColor.multiply(inateReflColor);
			}

			/* Then add the reflected color*/
			pixelColor.add(reflColor);
		}
		else
		{
			pixelColor = s.getSkyColor();
		}
	}
}
void RayTracer::getDirectLightPath(Ray & ray, Scene & s, Intersection & hit, Color & pixelColor, int step)
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
		if (glm::dot(shadowRay.direction, hit.normal) > 0.0001f)
		{
			Intersection shadowHit;

			bool intercept = s.getClosestIntersect(shadowRay, shadowHit);

			if (intercept == false || shadowHit.dist > glm::length(lightPos - hit.position))
			{
				hit.mtl->computeReflectance(colors[i], shadowRay.direction, -1.0f * ray.direction, hit);
				pixelColor.add(colors[i]);
			}
		}
	}			
}
void RayTracer::getDirectLight(Ray & ray, Scene & s, Intersection & hit, Color & pixelColor)
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

RayTracer::~RayTracer()
{
}
