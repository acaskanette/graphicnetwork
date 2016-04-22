#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


class Camera
{
public:
	Camera();
	~Camera();

	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;

	glm::mat4 viewMatrix;

	float elapsedTime;

	float movementSpeed;

	void Update();

	void MoveUp(float speedMultiplier);
	void MoveDown(float speedMultiplier);
	void MoveForward(float speedMultiplier);
	void MoveBackward(float speedMultiplier);
	void MoveRight(float speedMultiplier);
	void MoveLeft(float speedMultiplier);


};




