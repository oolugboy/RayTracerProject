#include "Material.h"

void Material::setDiffuseColor(Color val)
{
	diffuseColor = val;
}
void Material::setSpecularColor(Color val)
{
	specularColor = val;
}
void Material::setDiffuseLevel(float level)
{
	this->diffuseLevel = level;
}
void Material::setSpecularLevel(float level)
{
	this->specularLevel = level;
}
void Material::seedRandomGenerator(float seed)
{
	srand(seed);
}
void Material::setRoughness(float roughU, float roughV)
{
	this->nU = roughU;
	this->nV = roughV;
}