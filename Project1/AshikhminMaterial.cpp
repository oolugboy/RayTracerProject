#include "AshikhminMaterial.h"
#include <iostream>

using namespace std;
float PI = 3.1415926f;
AshikhminMaterial::AshikhminMaterial()
{
	isLambertian = isDielectric = false;
	nU = nV = 0.0f;
	specularColor = Color(0.0f, 0.0f, 0.0f);
	diffuseColor = Color(0.0f, 0.0f, 0.0f);
	debug = false;
	step = 0;
}

AshikhminMaterial::~AshikhminMaterial()
{
}

void AshikhminMaterial::generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor)
{
	glm::vec3 diffuseDir, specularDir;
	generateDiffuseSample(isect, inDir, diffuseDir);

	float specDirProb = generateSpecularSample(isect, inDir, specularDir);

	float specProb = specularLevel / (diffuseLevel + specularLevel);

	float sample = (float)(rand() % 10) / 9.0f;

	if (sample > specProb)
	{
		outColor = diffuseColor;
		outColor.scale(1.0f - specProb);
		outDir = diffuseDir;
	}
	else
	{
		outColor = specularColor;
		outColor.scale(specProb);	
		outDir = specularDir;
	}
	if (glm::dot(outDir, isect.normal) < 0.000f)
	{
		outColor = Color(0.00000f);
	}
}
float AshikhminMaterial::getPhi(float eps1)
{
	float toTan = sqrt((nU + 1.0f) / (nV + 1.0f)) * tan((PI * eps1) / 2.0f);
	return atan(toTan);
}
float AshikhminMaterial::getTheta(float eps2, float phi)
{
	float exp = 1.0f / ((nU * pow(cos(phi), 2.0f)) + (nV * pow(sin(phi), 2.0f)) + 1.0f);
	return acos(pow(1.0f - eps2, exp));
}
float AshikhminMaterial::generateSpecularSample(const Intersection isect, const glm::vec3 inDir, glm::vec3 & outDir)
{
	float eps1 = (float)(rand() % 10) / 9.0f;
	float eps2 = (float)(rand() % 10) / 9.0f;

	float theta = 0.0f, phi = 0.0f;

	if (eps1 >= 0.25f && eps1 < 0.5f)
	{	
		phi = getPhi(1.0f - 4.0f * (0.5f - eps1));
		phi = (PI - phi);
	}
	else if (eps1 >= 0.50f && eps1 < 0.75f)
	{
		phi = getPhi(1.0f - 4.0f * (0.75f - eps1));
		phi += PI;
	}
	else if(eps1 >= 0.75f && eps1 <= 1.001f)
	{
		phi = getPhi(1.0f - 4.0f * (1.001 - eps1));
		phi = (2.0f * PI) - phi;
	}
	else
	{
		phi = getPhi(eps1);
	}

	theta = getTheta(eps2, phi);

	glm::vec3 h = getCartesianVector(isect, theta, phi);

	/*cout << " The theta is " << theta << " the phi " << phi << endl;
	cout << " The in " << inDir.x << " " << inDir.y << " " << inDir.z << endl;
	cout << " The h " << h.x << " " << h.y << " " << h.z << endl;*/
	outDir = (2.0f * glm::dot(inDir, h) * h) - inDir;
	
	float hProb =  getSpecularProbability(isect.normal, h, phi);
	return hProb / (4.0f * glm::dot(inDir, h));
}
float AshikhminMaterial::getSpecularProbability(glm::vec3 normal, glm::vec3 h, float phi)
{
	float leftOp = sqrt((nU + 1.0f) * (nV + 1.0f)) / (2 * PI);
	float exp = (nU * pow(cos(phi), 2)) + (nV * pow(sin(phi), 2));
	
	return leftOp * pow(glm::dot(normal, h), exp);
}
void AshikhminMaterial::generateDiffuseSample(const Intersection isect, const glm::vec3 inDir, glm::vec3 & outDir)
{
	float s = (float)(rand() % 10) / 9.0f;
	float t = (float)(rand() % 10) / 9.0f;

	float u = 2 * PI * s;
	float v = sqrt(1 - t);

	outDir = glm::normalize((v * cos(u) * isect.tangentU) + (sqrt(t) * isect.normal) + (v * sin(u) * isect.tangentV));
}
void AshikhminMaterial::seedRandomGenerator(int seed)
{
	srand(seed);
}
glm::vec3 AshikhminMaterial::getCartesianVector(const Intersection isect, float theta, float phi)
{
	glm::vec3 uOff = isect.tangentU * sin(theta) * cos(phi);
	glm::vec3 vOff = isect.tangentV * sin(theta) * sin(phi);
	glm::vec3 nOff = isect.normal * cos(theta);

	return glm::normalize(uOff + vOff + nOff);
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
	/*cout << " the leftOp is " << leftMostOp << " midOp " << midOp << " rightMostOp " << rightMostOp << endl;
	cout << " For midOp num " << pow(hDotN, exp) << " denum " << (hDotK * fmax(nDotK1, nDotK2)) << endl;
	cout << " The exp is " << exp << " the hDotN is " << hDotN << endl;*/
	
	return leftMostOp * midOp * rightMostOp;
}
float AshikhminMaterial::getShlickApprox(float kDotH)
{
	return specularLevel + (1.0f - specularLevel) * pow(1.0f - kDotH, 5);
}
float AshikhminMaterial::getDiffuseReflectance(const Intersection & isect, const glm::vec3 & inDir, const glm::vec3 & outDir)
{
	float thirdOp = (1.0f - pow(1.0f - (glm::dot(isect.normal, inDir) / 2.0f), 5));

	float fourthOp = (1.0f - pow(1.0f - (glm::dot(isect.normal, outDir) / 2.0f), 5));

	return ((28.0f * diffuseLevel) / (23.0f)) * (1.0f - specularLevel) * thirdOp * fourthOp;
}
void AshikhminMaterial::computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit)
{
	Color reflSpecularColor = specularColor;
	float scaleVal = getSpecularReflectance(hit, in, out);
	reflSpecularColor.scale(scaleVal);
	//cout << " The specular scale val is " << scaleVal << endl;

	Color reflDiffuseColor = diffuseColor;
	scaleVal = getDiffuseReflectance(hit, in, out);
	reflDiffuseColor.scale(scaleVal);
	//cout << " The diffuse scale val is " << scaleVal << endl;

	Color resReflectance = reflSpecularColor;
	resReflectance.add(reflDiffuseColor);
	col.multiply(resReflectance);
}