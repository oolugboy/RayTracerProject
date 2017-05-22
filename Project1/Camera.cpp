#include "Camera.h"
#include "Intersection.h"
#include "Material.h"

 Camera::Camera()
 {
	 count = 0;
	 superSampler = false;
	 jitter = shirley = false;
	 rayTracer = new RayTracer();
	 srand(0);
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
			if (superSampler)
			{
				superSamplePixel(x, y, s);
				//cout << " Done sampling pixel " << x << " " << y << endl;
			}
			else
			{
				samplePixel(x, y, s);
			}
		}
	}
 }
 void Camera::setSuperSample(float xSamples, float ySamples)
 {
	 this->xSamples = xSamples;
	 this->ySamples = ySamples;
 }
 void Camera::setJitter(bool jitter)
 {
	 this->jitter = jitter;
 }
 void Camera::setShirley(bool shirley)
 {
	 this->shirley = shirley;
 }
 void Camera::samplePixel(int x, int y, Scene & s)
 {
	 /* First get the direction of the ray */
	 float fx = (((float)x + 0.5f) / ((float)xRes)) - 0.5f;
	 float fy = (((float)y + 0.5f) / ((float)yRes)) - 0.5f;

	 Color pixelColor = Color(0.0f, 0.0f, 0.0f);
	 shootAtPixelOffset(fx, fy, s, pixelColor);

	 /* Set the color of the pixel */
	 bMP->SetPixel(x, y, pixelColor.ToInt());
 }
 void Camera::applyShirley(float & xRand, float & yRand)
 {
	 if (xRand < 0.5f)
	 {
		 xRand = -0.5f + sqrt(2.0f * xRand);
	 }
	 else
	 {
		 xRand = 1.5f - sqrt(2.0f - (2.0f * xRand));
	 }
	 if (yRand < 0.5f)
	 {
		 yRand = -0.5f + sqrt(2.0f * yRand);
	 }
	 else
	 {
		 yRand = 1.5f - sqrt(2.0f - (2.0f * yRand));
	 }
 }
 
 void Camera::superSamplePixel(int x, int y, Scene & s)
 {
	float baseFx = (float)x / (float)xRes, baseFy = (float)y / (float)yRes;
	int count = 0;
	Color pixelColor = Color(0.0f, 0.0f, 0.0f);
	for (int yOff = 0; yOff < ySamples; yOff++)
	{
		for (int xOff = 0; xOff < xSamples; xOff++)
		{
			float fx = baseFx + ((float)xOff / (xRes * xSamples));
			float fy = baseFy + ((float)yOff / (yRes * ySamples));

			float xRand = 0.0f, yRand = 0.0f;
			if (jitter)
			{
				xRand = (float)(rand() % 10) / 9.0f;
				yRand = (float)(rand() % 10) / 9.0f;
			}
			if (shirley)
			{
				applyShirley(xRand, yRand);
			}

			fx += xRand / (xRes * xSamples);
			fx -= 0.5f;
			fy += yRand / (yRes * ySamples);
			fy -= 0.5f;

			
			Color subPixelColor = Color(0.0f, 0.0f, 0.0f);
			shootAtPixelOffset(fx, fy, s, subPixelColor);
			pixelColor.scale(count);
			pixelColor.add(subPixelColor);
			pixelColor.scale(1.0f / (float)(count + 1));
			count++;
		}
	}
	bMP->SetPixel(x, y, pixelColor.ToInt());
}
 void Camera::makeSuperSampler()
 {
	 superSampler = true;
 }
 void Camera::shootAtPixelOffset(float fx, float fy, Scene & s, Color & pixelColor)
 {
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

	 if (superSampler)
	 {
		//Temp
		 rayTracer->pathTrace(ray, s, pixelColor, 1);
	 }
	 else
	 {
		 rayTracer->rayTrace(ray, s, pixelColor);
	 }	
 }
 void Camera::saveBitmap(char * filename)
 {
	 bMP->SaveBMP(filename);
 }
 Camera::~Camera()
 {
	 delete(bMP);
 }