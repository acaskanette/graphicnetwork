#include "Trackball.h"
#include <GL/glew.h>
#include "VMath.h"
#include "MMath.h"


using namespace MATH;
//using namespace GAME;

Trackball::Trackball()
{

	//currentPosition = Vec4(0.0f);
	//newPosition = Vec4(0.0f);
	mouseRotationMatrix = Matrix4(1.0f);
}


Trackball::~Trackball()
{
}


void Trackball::OnLeftMouseButtonDown(int x, int y){ 
	
	// Get viewport information
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport); // returns array with [x, y,width, height]
	
	// Set start point of vector to be the point, relative to the viewport
	currentPosition = Vec3(float(x - viewport[2] / 2), float(viewport[3] / 2) - y, 0.0f);

}

void Trackball::OnMouseMove(int x, int y){

	// Get viewport information
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport); // returns array with [x, y,width, height]

	// Set end point of vector based on where you have moved to
	newPosition = Vec3(float(x - viewport[2] / 2), float(viewport[3] / 2 - y), 0.0f);

	// Calculate magnitude of the resultant vector to determine magnitude of rotation on object
	float magnitude = VMath::mag(newPosition - currentPosition);
	// Make sure we don'tend up dividing by zero during cross product
	if (magnitude < VERY_SMALL) return;

	// Otherwise, let's create the new rotation matrix
	Vec3 mouseMoveDirection = VMath::normalize(newPosition - currentPosition);
	Vec3 rotationAxis = VMath::cross(Vec3(0.0f, 0.0f, 1.0f), mouseMoveDirection);

	mouseRotationMatrix = MMath::rotate(magnitude, rotationAxis.x, rotationAxis.y, rotationAxis.z) * mouseRotationMatrix;
	currentPosition = newPosition;

}