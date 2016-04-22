#pragma once
#include "RenderObject.h"


class LitCube :
	public RenderObject
{
public:
	LitCube();
	~LitCube();

	glm::vec3 lightPosition;

	virtual void Render(Camera* camera);
	virtual void Update();

	float timeElapsed;
};

