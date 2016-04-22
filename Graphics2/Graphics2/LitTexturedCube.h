#pragma once
#include "RenderObject.h"

class LitTexturedCube :
	public RenderObject
{
public:
	LitTexturedCube();
	~LitTexturedCube();

	glm::vec3 lightPosition;

	virtual void Render(Camera* camera);
	virtual void Update();

	float timeElapsed;
};

