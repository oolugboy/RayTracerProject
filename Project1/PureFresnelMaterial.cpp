#include "PureFresnelMaterial.h"
#include <iostream>

using namespace std;
PureFresnelMaterial::PureFresnelMaterial()
{
	isDielectric = true;
}
void PureFresnelMaterial::computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit)
{

}
void PureFresnelMaterial::generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor)
{
	glm::vec3 reflDir, refrDir;
	generateReflectedSample(isect, inDir, reflDir);

	generateRefractedSample(isect, inDir, refrDir);

	float refrProb = getRefractedLightProp(isect, inDir, refrDir);

//	cout << " The refrProb is " << refrProb << endl;

	float randVal = (float)rand() / (float)RAND_MAX;

	outColor = diffuseColor;

	if (randVal <= refrProb)
	{
		outDir = refrDir;
		//outColor.scale(refrProb);	
	}
	else
	{
		outDir = reflDir;
		//outColor.scale(1.0f - refrProb);
	}
}
void PureFresnelMaterial::setRefractiveIndex(float n)
{
	this->n = n;
}
void PureFresnelMaterial::generateReflectedSample(const Intersection isect, const glm::vec3 inDir, glm::vec3 &outDir)
{
	outDir = (2.0f * glm::dot(inDir, isect.normal) * isect.normal) - inDir;
}
float PureFresnelMaterial::getRefractedLightProp(const Intersection isect, const glm::vec3 inDir, const glm::vec3 outDir)
{
	glm::vec3 normal = isect.normal;

	if (glm::dot(inDir, normal) < 0.00f)
	{
		normal = normal * -1.0f;
		ni = n;
		nt = 1.003f;
	}
	else
	{
		ni = 1.003f;
		nt = n;
	}

	float rParNum = (nt * glm::dot(normal, inDir)) + (ni * glm::dot(normal, outDir));
	float rParDenum = (nt * glm::dot(normal, inDir)) - (ni * glm::dot(normal, outDir));

	float rPar = rParNum / rParDenum;

	float rPerpNum = (ni * glm::dot(normal, inDir)) + (nt * glm::dot(normal, outDir));
	float rPerpDenum = (ni * glm::dot(normal, inDir)) - (nt * glm::dot(normal, outDir));

	float rPerp = rPerpNum / rPerpDenum;

	return 1.0f - (0.5f * (pow(rPar, 2.0f) + pow(rPerp, 2.0f)));
}
void PureFresnelMaterial::generateRefractedSample(const Intersection isect, const glm::vec3 inDir, glm::vec3 & outDir)
{
	glm::vec3 normal = isect.normal;
	if (glm::dot(normal, inDir) < 0.00f)
	{		
		normal = normal * -1.0f;
		ni = n;
		nt = 1.003f;
	}
	else
	{
		ni = 1.003f; // Assuming its always air;
		nt = n;
	}

	glm::vec3 z = (ni / nt) * ((glm::dot(normal, inDir) * normal) - inDir);
	if (glm::length(z) > 1.0f)
	{
		outDir = (2.0f * glm::dot(normal, inDir) * normal) - inDir;
	}
	else
	{
		outDir = z - (sqrt(1.0f - pow(glm::length(z), 2)) * normal);
	}
}
PureFresnelMaterial::~PureFresnelMaterial()
{
	
}
