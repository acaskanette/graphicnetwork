#pragma once
#include "RenderObject.h"
class TexturedCube :
	public RenderObject
{
public:
	TexturedCube();
	~TexturedCube();

	virtual void Render();
	virtual void Update();

	float timeElapsed;


};

