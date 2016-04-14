#pragma once
#include "RenderObject.h"

class Triangle :
	public RenderObject
{
public:
	Triangle();
	~Triangle();

	virtual void Render();
	virtual void Update();

	float timeElapsed;

};

