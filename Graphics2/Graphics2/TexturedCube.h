#pragma once
#include "RenderObject.h"

class Camera;

class TexturedCube :
	public RenderObject
{
public:
	TexturedCube();
	~TexturedCube();

	virtual void Render(Camera* camera);
	virtual void Update();

	float timeElapsed;

	//Camera* camera;

};

