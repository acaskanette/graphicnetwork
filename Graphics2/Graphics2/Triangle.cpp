#include "Triangle.h"


Triangle::Triangle()
{

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	// Generate and Bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// Create buffer
	glGenBuffers(1, &VBO);
	// Copy vertex data to buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Set vertex attrib pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//Unbind VAO
	glBindVertexArray(0);
	// Compile and bind Shaders to program
	program = LoadShaders("vertex-Triangle.glsl", "fragment-Triangle.glsl");
	

}


Triangle::~Triangle()
{
}

void Triangle::Render() {
	
	glUseProgram(program);				// Set active program
	glBindVertexArray(VAO);				// Set active VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);	// Draw from that VAO
	glBindVertexArray(0);				// Reset active VAO

}
