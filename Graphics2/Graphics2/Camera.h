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
	glm::vec3 target;
	glm::vec3 up;

	glm::mat4 viewMatrix;

	float elapsedTime;

	void Update();



};




