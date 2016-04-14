#include "Camera.h"
#include <gl\glew.h>

Camera::Camera()
{

	position = glm::vec3(0.0f, 0.0f, 3.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	viewMatrix = glm::lookAt(position, target, up);

	elapsedTime = 0.0f;

}


Camera::~Camera()
{
}


void Camera::Update() {

	elapsedTime += 0.016f;

	GLfloat radius = 10.0f;
	GLfloat camX = sin(elapsedTime) * radius;
	GLfloat camZ = cos(elapsedTime) * radius;
	position = glm::vec3(camX, 0, camZ);


	viewMatrix = glm::lookAt(position, target, up);

}