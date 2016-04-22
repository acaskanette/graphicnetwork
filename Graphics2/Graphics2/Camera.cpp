#include "Camera.h"
#include <gl\glew.h>

Camera::Camera()
{
	movementSpeed = 1.0f;

	position = glm::vec3(0.0f, 0.0f, 3.0f);
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	viewMatrix = glm::lookAt(position, position + forward, up);

	elapsedTime = 0.0f;

}


Camera::~Camera()
{
}


void Camera::Update() {

	elapsedTime += 0.016f;

	//GLfloat radius = 10.0f;
	//GLfloat camX = sin(elapsedTime) * radius;
	//GLfloat camZ = cos(elapsedTime) * radius;
	//position = glm::vec3(camX, 0, camZ);


	viewMatrix = glm::lookAt(position, position + forward, up);

}


void Camera::MoveUp(float speedMultiplier) {

	position += up * speedMultiplier * movementSpeed;

}

void Camera::MoveDown(float speedMultiplier) {
	
	position -= up * speedMultiplier * movementSpeed;

}

void Camera::MoveForward(float speedMultiplier) {

	position += forward * speedMultiplier * movementSpeed;

}

void Camera::MoveBackward(float speedMultiplier) {

	position -= forward * speedMultiplier * movementSpeed;

}

void Camera::MoveRight(float speedMultiplier) {

	position += glm::normalize(glm::cross(forward, up)) * speedMultiplier * movementSpeed;

}

void Camera::MoveLeft(float speedMultiplier) {

	position -= glm::normalize(glm::cross(forward, up)) * speedMultiplier * movementSpeed;

}