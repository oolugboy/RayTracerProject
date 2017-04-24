#include "BoxTreeNode.h"
#include <limits>
#include <algorithm>

int BoxTreeNode::rCounter = 0;
BoxTreeNode::BoxTreeNode()
{
	numTriangles = 0;
}

void BoxTreeNode::fillBoxDimensions(int count, Triangle * tri)
{
	/*cout << "About to fill the dimensions " << endl;
	cout << " The fillDim amount of triangles is " << count << endl;*/
	maxX = maxY = maxZ = -10000.0f;
	minX = minY = minZ = 10000.0f;	

	//cout << " The position " << tri[0].getVtx(0)->position.x << endl;
	for (int i = 0; i < count; i++)
	{		


		maxX = fmax(maxX, tri[i].getVtx(0)->position.x); minX = fmin(minX, tri[i].getVtx(0)->position.x);		
		maxX = fmax(maxX, tri[i].getVtx(1)->position.x); minX = fmin(minX, tri[i].getVtx(1)->position.x);
		maxX = fmax(maxX, tri[i].getVtx(2)->position.x); minX = fmin(minX, tri[i].getVtx(2)->position.x);

		maxY = fmax(maxY, tri[i].getVtx(0)->position.y); minY = fmin(minY, tri[i].getVtx(0)->position.y);
		maxY = fmax(maxY, tri[i].getVtx(1)->position.y); minY = fmin(minY, tri[i].getVtx(1)->position.y);
		maxY = fmax(maxY, tri[i].getVtx(2)->position.y); minY = fmin(minY, tri[i].getVtx(2)->position.y);

		maxZ = fmax(maxZ, tri[i].getVtx(0)->position.z); minZ = fmin(minZ, tri[i].getVtx(0)->position.z);
		maxZ = fmax(maxZ, tri[i].getVtx(1)->position.z); minZ = fmin(minZ, tri[i].getVtx(1)->position.z);
		maxZ = fmax(maxZ, tri[i].getVtx(2)->position.z); minZ = fmin(minZ, tri[i].getVtx(2)->position.z);

	}

	/*cout << " The max " << maxX << " " << maxY << " " << maxZ << endl;
	cout << " The min " << minX << " " << minY << " " << minZ << endl;*/

}
void BoxTreeNode::getLargestAxis(bool & xAxis, bool & yAxis, bool & zAxis)
{
	//cout << " In get largest axis " << endl;
	float xDist = maxX - minX;
	float yDist = maxY - minY;
	float zDist = maxZ - minZ;
	
	if (xDist >= yDist && xDist >= zDist)
	{
		//cout << " x is biggest " << endl;
		xAxis = true;
	}
	else if (yDist >= xDist && yDist >= zDist)
	{
		//cout << " y is biggest " << endl;
		yAxis = true;
	}
	else
	{
		//cout << " z is biggest " << endl;
		zAxis = true;
	}
}
void BoxTreeNode::printVector(glm::vec3 val)
{
	cout << val.x << " " << val.y << " " << val.z << endl;
}
pair<int, int> BoxTreeNode::groupTriangles(int count, Triangle * tri1, Triangle * tri2, Triangle * tri)
{
	int count1 = 0, count2 = 0;

	for (int i = 0; i < count; i++)
	{
		/*cout << " The vertices " << endl;
		printVector(tri[i].getVtx(0)->position);
		printVector(tri[i].getVtx(1)->position);
		printVector(tri[i].getVtx(2)->position); */

		glm::vec3 center = (tri[i].getVtx(0)->position + tri[i].getVtx(1)->position + tri[i].getVtx(2)->position) / 3.0f;
		tri[i].center = center;
		/*cout << " The center is ";
		printVector(center);*/
		
		tri[i].xAxis = xAxis;
		tri[i].yAxis = yAxis;
		tri[i].zAxis = zAxis;

		if (xAxis)
		{		
			//float xCenter = aveX;
			float xCenter = minX + ((maxX - minX) / 2.0f);
			//cout << " The xCenter is " << xCenter << endl;
			if (center.x < xCenter)
			{
				tri1[count1++] = tri[i];
			}
			else
			{
				tri2[count2++] = tri[i];
			}
		}
		if (yAxis)
		{
			//int yCenter = aveY;
			float yCenter = minY + ((maxY - minY) / 2.0f);
		//	cout << " The yCenter is " << yCenter << endl;
			if (center.y < yCenter)
			{
				tri1[count1++] = tri[i];
			}
			else
			{
				tri2[count2++] = tri[i];
			}
		}
		if (zAxis)
		{
			//int zCenter = aveZ;
			float zCenter = minZ + ((maxZ - minZ) / 2.0f);
		//	cout << " The zCenter is " << zCenter << endl;
			if (center.z < zCenter)
			{
				tri1[count1++] = tri[i];
			}
			else
			{
				tri2[count2++] = tri[i];
			}
		}
	}
	return make_pair(count1, count2);
}
bool myFunction(const Triangle a, const Triangle b) 
{ 
	if(a.xAxis)
		return (a.center.x < a.center.x);
	else if(a.yAxis)
		return (a.center.y < b.center.y);
	else
		return (a.center.z < b.center.z);
}
void BoxTreeNode::construct(int count, Triangle * tri)
{	
	//cout << " In the box tree node with " << count << " triangles " << endl;
	fillBoxDimensions(count, tri);

	/* If this is a leaf node */
	if (count <= maxTriangleNum)
	{
		//cout << " I have not children " << endl;
		numTriangles = count;
		for (int i = 0; i < count; i++)
		{
			triangles[i] = tri[i];
		/*	cout << " The leaf triangle vertices " << endl;
			printVector(tri[i].getVtx(0)->position);
			printVector(tri[i].getVtx(1)->position);
			printVector(tri[i].getVtx(2)->position); */
		}
		return;
	}

	xAxis = yAxis = zAxis = false;
	getLargestAxis(xAxis, yAxis, zAxis);

	Triangle * tri1 = new Triangle [count];
	Triangle * tri2 = new Triangle [count];

	pair<int, int> counts = groupTriangles(count, tri1, tri2, tri);

	if (counts.first == 0)
	{		
		sort(tri2, tri2 + counts.second, myFunction);
		int flHalf = counts.second / 2;
		for (int i = 0; i < flHalf; i++)
		{
			tri1[i] = tri2[i];		
		}
		//Shift back from the offsets 
		for (int i = 0; i < counts.second - flHalf; i++)
		{
			tri2[i] = tri2[i + flHalf];
		}

		//Update the new counts 
		counts.first = flHalf;
		counts.second = counts.second - flHalf;
	}

	if (counts.second == 0)
	{
		sort(tri1, tri1 + counts.first, myFunction);
		int flHalf = counts.first / 2;
		
		for (int i = 0; i < flHalf; i++)
		{
			tri2[i] = tri1[i + (counts.first - flHalf)];
		}
	
		//Update the counts 
		counts.second = flHalf;
		counts.first = counts.first - flHalf;
	}

	child1 = new BoxTreeNode();
	child1->construct(counts.first, tri1);

	child2 = new BoxTreeNode();
	child2->construct(counts.second, tri2);

	delete[] tri1;
	delete[] tri2;
}
bool BoxTreeNode::intersect(const Ray & ray, Intersection & hit)
{
	bool intersect = false;
	if (child1 && child2) // Assuming alwasys have two 
	{	
		Intersection bHit1, bHit2;
		bool boxFirst = child1->boxIntersect(ray, bHit1);
		bool boxSecond = child2->boxIntersect(ray, bHit2);

		if(boxFirst && boxSecond)
			intersect = (child1->intersect(ray, hit) || child2->intersect(ray, hit));
		else
		{
			if (boxFirst)
				intersect = (child1->intersect(ray, hit));
			if (boxSecond)
				intersect = (child2->intersect(ray, hit));
		}
	}
	else
	{
		for (int i = 0; i < numTriangles; i++)
		{
			if (triangles[i].intersect(ray, hit))
			{
				intersect = true;
				/*cout << " The hit position is ";
				printVector(hit.position);
				cout << " The hit dist is " << hit.dist << endl;*/
			}
		}		
	}
	return intersect;
}
bool BoxTreeNode::closestIntersect(const Ray & ray, Intersection & hit)
{	
	/*cout << " In the closest intersect " << endl;
	cout << " The max " << maxX << " " << maxY << " " << maxZ << endl;
	cout << " The min " << minX << " " << minY << " " << minZ << endl;*/
	bool intersect = false;
	if (child1 && child2)
	{		
		Intersection bHit1, bHit2;
		bool boxFirst = child1->boxIntersect(ray, bHit1);
		bool boxSecond = child2->boxIntersect(ray, bHit2);

		//cout << " The boxes " << boxFirst << " " << boxSecond << endl;
		
		if (boxFirst && boxSecond)
		{
			Intersection hit1, hit2;
			bool intersect1 = child1->closestIntersect(ray, hit1);
			bool intersect2 = child2->closestIntersect(ray, hit2);
			intersect = (intersect1 || intersect2);
	
			if (intersect1 && intersect2)
			{
				if (hit1.dist < hit2.dist)
				{
					hit = hit1;
				}
				else
				{
					hit = hit2;
				}
			}
			else
			{
				if (intersect1)
					hit = hit1;
				if(intersect2)
					hit = hit2;
			}			
		}
		else
		{
			if (boxFirst)
				intersect = child1->closestIntersect(ray, hit);
			if (boxSecond)
				intersect = child2->closestIntersect(ray, hit);
		}
	}
	else
	{
		//cout << " No child case " << endl;
		Intersection tHit;
		for (int i = 0; i < numTriangles; i++)
		{
			if (triangles[i].intersect(ray, tHit))
			{
				intersect = true;
				if (tHit.dist < hit.dist)
				{
					hit = tHit;
				}
			}
		}
	}
	//cout << " The intersect returned is " << intersect << endl;
	return intersect;
}
bool BoxTreeNode::boxIntersect(const Ray & ray, Intersection & hit)
{
	float tx1 = 0, tx2 = 0, ty1 = 0, ty2 = 0, tz1 = 0, tz2 = 0;
	
	if (ray.direction.x == 0)
	{
		if (ray.origin.x < minX || ray.origin.x > maxX)
			return false;
	}
	else
	{
		tx1 = (minX - ray.origin.x) / ray.direction.x;
		tx2 = (maxX - ray.origin.x) / ray.direction.x;
	}
	if (ray.direction.y == 0)
	{
		if (ray.origin.y < minY || ray.origin.y > maxY)
			return false;	
	}
	else
	{
		ty1 = (minY - ray.origin.y) / ray.direction.y;
		ty2 = (maxY - ray.origin.y) / ray.direction.y;
	}
	if (ray.direction.z == 0)
	{
		if (ray.origin.z < minZ || ray.origin.z > maxZ)
			return false;
	}
	else
	{
		tz1 = (minZ - ray.origin.z) / ray.direction.z;
		tz2 = (maxZ - ray.origin.z) / ray.direction.z;
	}

	float tMin = fmax(fmin(tx1, tx2), fmin(ty1, ty2));
	tMin = fmax(tMin, fmin(tz1, tz2));
	 
	float tMax = fmin(fmax(tx1, tx2), fmax(ty1, ty2));
	tMax = fmin(tMax, fmax(tz1, tz2));

	//cout << " The tMin " << tMin << " and tMax " << tMax << endl;
	if (tMax < 0.0f) // Assuming that the ray is never inside the box
	{
		return false;
	}
	else if (tMin <= tMax)
	{
		if (tMin < 0.0f)
		{
			hit.dist = tMax;
		}
		else
		{
			hit.dist = tMin;
		}
		hit.position = ray.origin + (hit.dist * ray.direction);
		return true;
	}
	else
	{
		return false;
	}
}
BoxTreeNode::~BoxTreeNode()
{
}
