#pragma once

#include "SceneObject.h"


class Camera 
{
public:
	Camera();
	~Camera();

private:
	
	GLfloat projectionMatrixLocation;
	GLfloat cameraViewMatrixLocation;
};

