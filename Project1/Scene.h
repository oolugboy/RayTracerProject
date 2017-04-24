////////////////////////////////////////
// Scene.h
////////////////////////////////////////

#pragma once

#include "Object.h"
#include "Light.h"
#include <vector>

////////////////////////////////////////////////////////////////////////////////

class Scene {
public:
	Scene()		
	{
		skyColor.set(0.2f,0.2f,0.5f);
		shadows = true;
	}

	void addObject(Object &obj)				
	{
		objects.push_back(&obj);
	}
	void addLight(Light &lgt)				
	{
		lights.push_back(&lgt);
	}
	void setSkyColor(const Color sky)		
	{
		skyColor=sky;
	}

	int getNumLights()						
	{
		return lights.size();
	}
	Light & getLight(int i)						
	{
		return * lights[i];
	}
	Color getSkyColor()						
	{
		return skyColor;
	}

	bool intersect(const Ray &ray,Intersection &hit) {

		bool success=false;
		for(unsigned int i=0;i< objects.size();i++)
			if(objects[i]->intersect(ray,hit)) success=true;
		return success;
	}
	bool getClosestIntersect(const Ray & ray, Intersection & hit)
	{	
		bool success = false;
		Intersection closestHit = Intersection();
		//cout << " The amount of objects is " << objects.size() << endl;
		for (int i = 0; i < objects.size(); i++)
		{
			//cout << " The scene i is " << i << endl;
			if (objects[i]->closestIntersect(ray, hit))
			{				
				success = true;
				if (hit.dist < closestHit.dist)
				{
					closestHit = hit;
				}
			}
		}
	//	cout << " Done with the scene loop " << endl;
		hit = closestHit;
		return success;
	}
	bool shadows;
private:
	std::vector<Object*> objects;
	std::vector<Light*> lights;
	Color skyColor;
};

////////////////////////////////////////////////////////////////////////////////
