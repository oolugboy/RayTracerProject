#include "BoxTreeObject.h"


BoxTreeObject::BoxTreeObject()
{
	rootNode = new BoxTreeNode();
}

void BoxTreeObject::construct(MeshObject & mesh)
{
	clock_t t;
	t = clock();
	rootNode->construct(mesh.getNumTriangles(), mesh.getTrianglesPointer());
	t = clock() - t;
	cout << " Bounding hierarchy constructed in " << ((float)t) / CLOCKS_PER_SEC << " seconds. " << endl;;
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
