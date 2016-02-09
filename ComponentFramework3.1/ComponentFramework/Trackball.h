#pragma once

#include "Matrix.h"

class Trackball
{
public:
	Trackball();
	~Trackball();

	void OnLeftMouseButtonDown(int x, int y);
	void OnMouseMove(int x, int y);

	MATH::Matrix4 mouseRotationMatrix;
	MATH::Vec3 currentPosition;
	MATH::Vec3 newPosition;
};

