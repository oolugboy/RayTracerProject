#include "Camera.h"
#include "Intersection.h"
#include "Material.h"

 Camera::Camera()
 {
	 count = 0;
 }
 void Camera::setFOV(float f)
 {
	 verticalFOV = f;
 }
 void Camera::setAspect(float a)
 {
	 aspect = a;
 }
 void Camera::setResolution(int x, int y)
 {
	 xRes = x;
	 yRes = y;

	 bMP = new Bitmap(x, y);	 
 }
 void Camera::lookAt(glm::vec3 & pos, glm::vec3 & target, glm::vec3 & up)
 {
	 glm::vec3 d = pos;
	 glm::vec3 c = glm::normalize(d - target);
	 glm::vec3 a = glm::normalize(glm::cross(up, c));
	 glm::vec3 b = glm::cross(c, a);

	 worldMatrix = glm::mat4(a.x, a.y, a.z, 0, b.x, b.y, b.z, 0, c.x, c.y, c.z, 0, d.x, d.y, d.z, 1);
 }
 void Camera::render(Scene & s)
 {
	for (int y = 0; y < yRes; y++)
	{
		for (int x = 0; x < xRes; x++)
		{
			renderPixel(x, y, s);
		}
	}
 }

 void Camera::colorPixel(Ray ray, int x, int y, Scene & s)
 {
	 Intersection hit = Intersection();

	// cout << " The camera calling closest intersect " << endl;
	 bool collided = s.getClosestIntersect(ray, hit);

	 Color pixelColor = Color(0.0f, 0.0f, 0.0f);

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
				 if (intercept)
				 {
					//cout << " The hit dist is " << shadowHit.dist << " light dist " << glm::length(lightPos - hit.position) << endl;
				 }
				
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
	 /* Set the color of the pixel */
	 bMP->SetPixel(x, y, pixelColor.ToInt());	
 }
 void Camera::renderPixel(int x, int y, Scene & s)
 {
	 /* First get the direction of the ray */
	 float fx = (((float)x + 0.5f)/ ((float)xRes)) - 0.5f;
	 float fy = (((float)y + 0.5f) / ((float)yRes)) - 0.5f;

	 float PI = 3.14159265;
	 float radVFOV = (verticalFOV * PI) / 180.0f;
	 float radHFOV = 2.0f * atan(aspect * tan(radVFOV / 2.0f));

	 glm::vec3 a = glm::vec3(worldMatrix[0]);
	 glm::vec3 b = glm::vec3(worldMatrix[1]);
	 glm::vec3 c = glm::vec3(worldMatrix[2]);
	 glm::vec3 d = glm::vec3(worldMatrix[3]);

	 float scaleX = 2.0f * tan(radHFOV / 2.0f);
	 float scaleY = 2.0f * tan(radVFOV / 2.0f);

	 /* Now to get the color of the pixel */
	 Ray ray;
	 ray.origin = d;
	 ray.direction = glm::normalize((fx * scaleX * a) + (fy * scaleY * b) - c);

	 colorPixel(ray, x, y, s);

 }
 void Camera::saveBitmap(char * filename)
 {
	 bMP->SaveBMP(filename);
 }
 Camera::~Camera()
 {
	 delete(bMP);
 }