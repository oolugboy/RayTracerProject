#pragma once
#include "MeshObject.h"
#include "BoxTreeNode.h"
class BoxTreeObject :public Object
{
public:
	BoxTreeObject();
	~BoxTreeObject();
	void construct(MeshObject & mesh);
	bool intersect(const Ray & ray, Intersection & hit);
	bool closestIntersect(const Ray & ray, Intersection & hit);
private:
	BoxTreeNode * rootNode;
};

