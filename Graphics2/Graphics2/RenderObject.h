#pragma once
// SDL and Glew
#include <SDL.h>
#include <gl\glew.h>
// Utilities
#include <string>
// Image loader
#include <SOIL.h>
// GLM - Vectors and Matrices
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class RenderObject
{

public:

	// Transform	
	glm::mat4 translationMatrix;

	// For image loading
	int width, height;
	unsigned char* image;

	// OpenGL Properties
	GLuint VAO;
	GLuint VBO;
	GLuint program;
	GLuint texture0, texture1;
	GLuint transformMatrixLocation;

	RenderObject();
	~RenderObject();

	GLuint LoadShaders(const char * vertexFileName, const char * fragmentFileName);
	std::string ReadFile(const char *filePath);

	virtual void Render() = 0;
	virtual void Update() = 0;
};

