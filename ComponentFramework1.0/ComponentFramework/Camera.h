#pragma once

#include "SceneObject.h"


class Camera :
	public SceneObject
{
public:
	Camera();
	~Camera();

private:
	
	GLfloat projectionMatrixLocation;
	GLfloat cameraViewMatrixLocation;
};

