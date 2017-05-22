#include "AshikhminMaterial.h"
AshikhminMaterial::AshikhminMaterial()
{
	isDielectric = false;
}

AshikhminMaterial::~AshikhminMaterial()
{
}

void AshikhminMaterial::generateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor)
{

}
Color AshikhminMaterial::getSpecularReflectance(const Intersection &isect, const glm::vec3 &inDir, const glm::vec3 &outDir)
{
	float PI = 3.1415926f;

	float leftMostOp = sqrt((nU + 1.0f) * (nV + 1.0f)) / (8.0f * PI);

	glm::vec3 h = glm::normalize(inDir + outDir);
	float hDotU = glm::dot(h, isect.tangentU);
	float hDotV = glm::dot(h, isect.tangentV);
	float hDotN = glm::dot(h, isect.normal);
	float hDotK = glm::dot(h, inDir);
	float nDotK1 = glm::dot(isect.normal, inDir);
	float nDotK2 = glm::dot(isect.normal, outDir);

	float exp = ((nU * pow(hDotU, 2)) + (nV  * pow(hDotV, 2))) / (1.0f - pow(hDotN, 2));
	float midOp = pow(hDotN, exp) / (hDotK * fmax(nDotK1, nDotK2));
	
	Color rightMostOp = getShlickApprox(hDotK);
	rightMostOp.scale(midOp * leftMostOp);

	return rightMostOp;
}
Color AshikhminMaterial::getShlickApprox(float kDotH)
{
	//(- Rs + 1)(1 - (k.h))^5
	Color resSpecColor = specularColor;
	resSpecColor.scale(-1.0f);
	resSpecColor.add(Color::WHITE);
	float mult = pow(1.0f - kDotH, 5);
	resSpecColor.scale(mult);

	//Rs + (-Rs + 1)(1 - (k.h))^5
	resSpecColor.add(specularColor);

	return resSpecColor;
}
Color AshikhminMaterial::getDiffuseReflectance(const Intersection & isect, const glm::vec3 & inDir, const glm::vec3 & outDir)
{
	float PI = 3.1415926f;
	Color tempDiffuseOp = diffuseColor;
	tempDiffuseOp.scale(28.0f / (23.0f * PI));

	Color tempSpecularOp = specularColor;
	tempSpecularOp.scale(-1.0f);
	tempSpecularOp.add(Color::WHITE);

	float thirdOp = (1.0f - pow(1.0f - (glm::dot(isect.normal, inDir) / 2.0f), 5));

	float fourthOp = (1.0f - pow(1.0f - (glm::dot(isect.normal, outDir) / 2.0f), 5));

	Color resDiffuseRefl = tempDiffuseOp;
	resDiffuseRefl.multiply(tempSpecularOp);
	resDiffuseRefl.scale(thirdOp * fourthOp);

	return resDiffuseRefl;
}
void AshikhminMaterial::computeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit)
{
	Color reflSpecularColor = getSpecularReflectance(hit, in, out);
	reflSpecularColor.scale(specularLevel);
	Color reflDiffuseColor = getDiffuseReflectance(hit, in, out);
	reflDiffuseColor.scale(diffuseLevel);

	Color resReflectance = reflSpecularColor;
	resReflectance.add(reflDiffuseColor);
	col.multiply(resReflectance);
}