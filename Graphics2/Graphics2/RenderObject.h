#pragma once

#include <SDL.h>
#include <gl\glew.h>
#include <string>

#include "Soil.h"

class RenderObject
{

public:

	// For image loading
	int width, height;
	unsigned char* image;

	
	GLuint VAO;
	GLuint VBO;
	GLuint program;
	GLuint texture;

	RenderObject();
	~RenderObject();

	GLuint LoadShaders(const char * vertexFileName, const char * fragmentFileName);
	std::string ReadFile(const char *filePath);

	virtual void Render() = 0;
};

