////////////////////////////////////////
// Main.cpp
////////////////////////////////////////

#include <iostream>
#include "MeshObject.h"
#include "InstanceObject.h" 
#include "Camera.h"
#include "PointLight.h"
#include "DirectLight.h"
#include "Color.h"
#include "Scene.h"
#include "PlaneObject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "SphereObject.h"
#include "BoxTreeObject.h"

using namespace std;
void project1();
void project2();
void spheres();
void testProject();

#define PI 3.1415927
////////////////////////////////////////////////////////////////////////////////

int main(int argc,char **argv) {
	//project1();	
	project2();
	//spheres();
	//testProject();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////


void spheres() {
	// Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.8f, 1.0f));
	// Create ground plane
	PlaneObject ground;
	scn.addObject(ground);
	// Create spheres
	for (int i = 0; i < 20; i++) {		
		float rad = glm::linearRand(0.25f, 0.5f);
		glm::vec3 pos(glm::linearRand(-5.0f, 5.0f), rad, glm::linearRand(-5.0f, 5.0f));
		SphereObject * sphere = new SphereObject(pos, rad);	
		scn.addObject(*sphere);
	}
	// Create lights
	DirectLight sunlgt;
	sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.setIntensity(1.0f);
	sunlgt.setDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	scn.addLight(sunlgt);

	// Create camera
	Camera cam;
	cam.lookAt(glm::vec3(-0.75f, 0.25f, 5.0f), glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	cam.setFOV(40.0f);
	cam.setAspect(1.33f);
	cam.setResolution(800, 600);

	// Render image
	cam.render(scn);
	cout << " about to save the spheres image " << endl;
	cam.saveBitmap("spheres.bmp");
}


void project1() {
	// Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.9f, 1.0f));
	scn.shadows = false;

	// Create boxes
	MeshObject box1;
	box1.makeBox(5.0f,0.1f,5.0f);
	scn.addObject(box1); 

	MeshObject box2;
	box2.makeBox(1.0f,1.0f,1.0f);
	//box2.m

	InstanceObject inst1 = InstanceObject();
	glm::mat4x4 mtx=glm::rotate(glm::mat4x4(), 0.5f, glm::vec3(1,0,0));
	mtx[3][1]=1.0f;
	inst1.setMatrix(mtx);
	inst1.setChild(box2);
	scn.addObject(inst1);

	InstanceObject inst2 = InstanceObject();
	mtx=glm::rotate(glm::mat4x4(), 1.0f, glm::vec3(0,1,0));
	mtx[3]=glm::vec4(-1,0,1,1);
	inst2.setMatrix(mtx);
	inst2.setChild(box2);
	scn.addObject(inst2); 

	// Create lights
	DirectLight sunlgt;
	sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.setIntensity(0.5f);
	sunlgt.setDirection(glm::vec3(-0.5f, -1.0f, -0.5f));
	scn.addLight(sunlgt);

	PointLight redlgt;
	redlgt.setBaseColor(Color(1.0f, 0.2f, 0.2f));
	redlgt.setIntensity(2.0f);
	redlgt.setPosition(glm::vec3(2.0f, 2.0f, 0.0f));
	scn.addLight(redlgt);

	// Create camera
	Camera cam;
	cam.lookAt(glm::vec3(2.0f,2.0f,5.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0,1,0));
	cam.setResolution(800,600);
	cam.setFOV(40.0f);
	cam.setAspect(1.33f); 

	// Render image
	cam.render(scn);
	cam.saveBitmap("project1.bmp"); 
}

void project2() {
	// Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.8f, 1.0f));

	// Create ground
	MeshObject ground;
	ground.makeBox(5.0f, 0.1f, 5.0f);
	/*BoxTreeObject groundTree;
	groundTree.construct(ground);*/
	scn.addObject(ground);

	// Create dragon
	MeshObject dragon;
	dragon.loadPLY("dragon.ply", 0);
	cout << " Done loading the ply " << endl;
	dragon.smooth();
	BoxTreeObject tree;
	//tree.construct(ground);
	tree.construct(dragon);
	scn.addObject(tree); 

	// Create instance
	InstanceObject inst;
	inst.setChild(tree);
	glm::mat4x4 mtx = glm::eulerAngleY(PI);
	mtx[3] = glm::vec4(-0.05f, 0.0f, -0.1f, 1.0f);
	inst.setMatrix(mtx);
	scn.addObject(inst); 

	// Create lights
	DirectLight sunlgt;
	sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.setIntensity(1.0f);
	sunlgt.setDirection(glm::vec3(2.0f, -3.0f, -2.0f));
	scn.addLight(sunlgt);
	PointLight redlgt;
	redlgt.setBaseColor(Color(1.0f, 0.2f, 0.2f));
	redlgt.setIntensity(0.02f);
	redlgt.setPosition(glm::vec3(-0.2f, 0.2f, 0.2f));
	scn.addLight(redlgt); 
	PointLight bluelgt;
	bluelgt.setBaseColor(Color(0.2f, 0.2f, 1.0f));
	bluelgt.setIntensity(0.02f);
	bluelgt.setPosition(glm::vec3(0.1f, 0.1f, 0.3f));
	scn.addLight(bluelgt);

	// Create camera
	Camera cam;
	cam.lookAt(glm::vec3(-0.1f, 0.1f, 0.2f), glm::vec3(-0.05f, 0.12f, 0.0f),
		glm::vec3(0, 1.0f, 0));
	cam.setFOV(40.0f);
	cam.setAspect(1.33f);
	cam.setResolution(800, 600);

	// Render image
	cam.render(scn);
	cam.saveBitmap("project2.bmp");
}
void testProject()
{
	// Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.9f, 1.0f));
	scn.shadows = false;

	// Create boxes
	MeshObject box1;
	box1.makeBox(5.0f, 0.1f, 5.0f);
	BoxTreeObject tree1;
	tree1.construct(box1);	
	scn.addObject(tree1);	

	/*MeshObject box2;
	box2.makeBox(1.0f, 1.0f, 1.0f);
	//box2.m

	InstanceObject inst1 = InstanceObject();
	glm::mat4x4 mtx = glm::rotate(glm::mat4x4(), 0.5f, glm::vec3(1, 0, 0));
	mtx[3][1] = 1.0f;
	inst1.setMatrix(mtx);
	inst1.setChild(box2);
	scn.addObject(inst1);

	InstanceObject inst2 = InstanceObject();
	mtx = glm::rotate(glm::mat4x4(), 1.0f, glm::vec3(0, 1, 0));
	mtx[3] = glm::vec4(-1, 0, 1, 1);
	inst2.setMatrix(mtx);
	inst2.setChild(box2);
	scn.addObject(inst2);*/

	// Create lights
	DirectLight sunlgt;
	sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.setIntensity(0.5f);
	sunlgt.setDirection(glm::vec3(-0.5f, -1.0f, -0.5f));
	scn.addLight(sunlgt);

	PointLight redlgt;
	redlgt.setBaseColor(Color(1.0f, 0.2f, 0.2f));
	redlgt.setIntensity(2.0f);
	redlgt.setPosition(glm::vec3(2.0f, 2.0f, 0.0f));
	scn.addLight(redlgt);

	PointLight bluelgt;
	bluelgt.setBaseColor(Color(0.2f, 0.2f, 1.0f));
	bluelgt.setIntensity(0.02f);
	//bluelgt.setPosition(glm::vec3(0.1f, 0.1f, 0.3f));
	bluelgt.setPosition(glm::vec3(-0.2f, 0.1f, 0.2f));
	scn.addLight(bluelgt);

	// Create camera
	Camera cam;
	cam.lookAt(glm::vec3(2.0f, 2.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0));
	cam.setResolution(800, 600);
	cam.setFOV(40.0f);
	cam.setAspect(1.33f);

	// Render image
	cam.render(scn);
	cam.saveBitmap("testProject.bmp");
}
////////////////////////////////////////////////////////////////////////////////