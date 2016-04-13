#pragma once

#include <SDL.h>
#include <gl\glew.h>
#include <string>

class RenderObject
{





public:
	
	GLuint VAO;
	GLuint VBO;
	GLuint program;

	RenderObject();
	~RenderObject();

	GLuint LoadShaders(const char * vertexFileName, const char * fragmentFileName);
	std::string ReadFile(const char *filePath);

	virtual void Render() = 0;
};

