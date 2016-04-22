#pragma once
#include "RenderObject.h"

class Triangle :
	public RenderObject
{
public:
	Triangle();
	~Triangle();

	virtual void Render(Camera* camera);
	virtual void Update();

	float timeElapsed;

};

