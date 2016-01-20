#pragma once
#include "SDL.h"
#include <gl\glew.h>
#include "glm\glm.hpp"		// Glm Math Library
#include "glm\gtc\matrix_transform.hpp"	// Include matrix rotation

class SceneObject
{
public:
	SceneObject(){};
	~SceneObject(){};

	// Prevents compiler from making weird (copy) constructors
	SceneObject(const SceneObject&) = delete;
	SceneObject(SceneObject&&) = delete;
	SceneObject& operator = (const SceneObject&) = delete;
	SceneObject& operator = (SceneObject&&) = delete;

	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() const = 0;	

private:
	GLfloat translationMatrixLocation;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

};

