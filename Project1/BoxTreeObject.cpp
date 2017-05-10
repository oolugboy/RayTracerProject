#include "BoxTreeObject.h"


BoxTreeObject::BoxTreeObject()
{
	rootNode = new BoxTreeNode();
}

void BoxTreeObject::construct(MeshObject & mesh)
{
	rootNode->construct(mesh.getNumTriangles(), mesh.getTrianglesPointer());
}
bool BoxTreeObject::intersect(const Ray & ray, Intersection & hit)
{
	return rootNode->intersect(ray, hit);
}
bool BoxTreeObject::closestIntersect(const Ray & ray, Intersection & hit)
{
	return rootNode->closestIntersect(ray, hit);
}
BoxTreeObject::~BoxTreeObject()
{

}
