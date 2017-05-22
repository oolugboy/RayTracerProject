#include "AshikhminMaterial.h"
#include <iostream>

using namespace std;
float PI = 3.1415926f;
AshikhminMaterial::AshikhminMaterial()
{
	isDielectric = false;
	nU = nV = 0.0f;
}

AshikhminMaterial::~AshikhminMaterial()
{
}

void AshikhminMaterial::generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor)
{
	glm::vec3 diffuseDir, specularDir;
	generateDiffuseSample(isect, inDir, diffuseDir);

}
float AshikhminMaterial::getPhi(float eps1)
{
	float toTan = sqrt((nU + 1) / (nV + 1)) * tan((PI * eps1) / 2.0f);
	return atan(toTan);
}
float AshikhminMaterial::getTheta(float eps2, float phi)
{
	float exp = 1.0f / ((nU * pow(cos(phi), 2.0f)) + (nV * pow(sin(phi), 2.0f)) + 1.0f);
	return acos(pow(1 - eps2, exp));
}
void AshikhminMaterial::generateSpecularSample(const Intersection isect, const glm::vec3 inDir, glm::vec3 & outDir)
{
	float eps1 = (float)(rand() % 10) / 9.0f;
	float eps2 = (float)(rand() % 10) / 9.0f;

	float rEps1 = (float)(rand() % 10) / 9.0f;

	float theta = 0.0f, phi = 0.0f;

	phi = getPhi(rEps1);

	if (eps1 >= 0.25f && eps1 < 0.5f)
	{	
		phi += (PI / 2.0f);
	}
	if (eps1 >= 0.50f && eps1 < 0.75f)
	{
		phi += (PI);
	}
	if(eps1 >= 0.75f && eps1 <= 1.0f)
	{
		phi += (3.0f * PI)/ 2.0f;
	}

	theta = getTheta(eps2, phi);

	glm::vec3 h = getCartesianVector(isect, theta, phi);
}
void AshikhminMaterial::generateDiffuseSample(const Intersection isect, const glm::vec3 inDir, glm::vec3 & outDir)
{
	float s = (float)(rand() % 10) / 9.0f;
	float t = (float)(rand() % 10) / 9.0f;

	float PI = 3.1415926f;
	float u = 2 * PI * s;
	float v = sqrt(1 - t);

	outDir = (v * cos(u) * isect.tangentU) + (sqrt(t) * isect.normal) + (v * sin(u) * isect.tangentV);
}
void AshikhminMaterial::seedRandomGenerator(int seed)
{
	srand(seed);
}
glm::vec3 AshikhminMaterial::getCartesianVector(const Intersection isect, float theta, float phi)
{
	glm::vec3 u = isect.tangentU;
	glm::vec3 v = tan(phi) * isect.tangentV;

	glm::vec3 gAxis = glm::normalize(u + v);

	return (gAxis * cos((PI / 2.0f) - theta)) + (isect.normal * sin((PI / 2.0f) - theta));
}
float AshikhminMaterial::getSpecularReflectance(const Intersection &isect, const glm::vec3 &inDir, const glm::vec3 &outDir)
{
	float leftMostOp = sqrt((nU + 1.0f) * (nV + 1.0f)) / (8.0f);

	glm::vec3 h = glm::normalize(inDir + outDir);
	float hDotU = glm::dot(h, isect.tangentU);
	float hDotV = glm::dot(h, isect.tangentV);
	float hDotN = glm::dot(h, isect.normal);
	float hDotK = glm::dot(h, inDir);
	float nDotK1 = glm::dot(isect.normal, inDir);
	float nDotK2 = glm::dot(isect.normal, outDir);

	float exp = ((nU * pow(hDotU, 2)) + (nV  * pow(hDotV, 2))) / (1.0f - pow(hDotN, 2));
	float midOp = pow(hDotN, exp) / (hDotK * fmax(nDotK1, nDotK2));
	
	float  rightMostOp = getShlickApprox(hDotK);

	return leftMostOp * midOp * rightMostOp;
}
float AshikhminMaterial::getShlickApprox(float kDotH)
{
	return specularLevel + (1.0f - specularLevel) * pow(1.0f - kDotH, 5);
}
float AshikhminMaterial::getDiffuseReflectance(const Intersection & isect, const glm::vec3 & inDir, const glm::vec3 & outDir)
{
	//float PI = 3.1415926f;

	float thirdOp = (1.0f - pow(1.0f - (glm::dot(isect.normal, inDir) / 2.0f), 5));

	float fourthOp = (1.0f - pow(1.0f - (glm::dot(isect.normal, outDir) / 2.0f), 5));

	return ((28.0f * diffuseLevel) /(23.0f)) * (1.0f - specularLevel) * thirdOp * fourthOp;
}
void AshikhminMaterial::computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit)
{
	Color reflSpecularColor = specularColor;
	float scaleVal = getSpecularReflectance(hit, in, out);
	//cout << " The specular scale val is " << scaleVal << endl;

	reflSpecularColor.scale(scaleVal);

	Color reflDiffuseColor = diffuseColor;
	scaleVal = getDiffuseReflectance(hit, in, out);
	//cout << " The diffuse scale val is " << scaleVal << endl;

	reflDiffuseColor.scale(scaleVal);

	Color resReflectance = reflSpecularColor;
	resReflectance.add(reflDiffuseColor);
	col.multiply(resReflectance);
	//col = resReflectance;
	//col.multiply(diffuseColor);
}