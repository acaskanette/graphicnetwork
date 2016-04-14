#include "Triangle.h"


Triangle::Triangle()
{

	translationMatrix = glm::rotate(translationMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	translationMatrix = glm::scale(translationMatrix, glm::vec3(0.5f, 0.5f, 0.5f));

	timeElapsed = 0.0f;

	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,   // Top Right
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	0.0f, 0.0f,   // Bottom Left
		-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f,    // Top Left 
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	0.0f, 0.0f,   // Bottom Left
		0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f   // Top Right
	};

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	image = SOIL_load_image("wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);

	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);


	image = SOIL_load_image("awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);

	glGenTextures(2, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// End Textures

	// Generate and Bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// Create buffer
	glGenBuffers(1, &VBO);
	// Copy vertex data to buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Set vertex attrib pointers
	// Vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Colours
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Co-ordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	//Unbind VAO
	glBindVertexArray(0);
	// Compile and bind Shaders to program
	program = LoadShaders("vertex-Triangle.glsl", "fragment-Triangle.glsl");
	
	transformMatrixLocation = glGetUniformLocation(program, "transformMatrix");

}


Triangle::~Triangle()
{
}

void Triangle::Render() {
	
	
	GLfloat greenValue = (sin(timeElapsed) / 2) + 0.5;
	GLint vertexColorLocation = glGetUniformLocation(program, "ourColor");
	
	glUseProgram(program);				// Set active program
	
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	glUniformMatrix4fv(transformMatrixLocation, 1, GL_FALSE, glm::value_ptr(translationMatrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(program, "ourTexture0"), 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(program, "ourTexture1"), 1);

	glBindVertexArray(VAO);				// Set active VAO
	glDrawArrays(GL_TRIANGLES, 0, 6);	// Draw from that VAO
	glBindVertexArray(0);				// Reset active VAO

}

void Triangle::Update() {
	
	timeElapsed += 0.016;

	translationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::translate(translationMatrix, glm::vec3(0.5f, -0.5f, 0.0f));
	translationMatrix = glm::rotate(translationMatrix, glm::radians(timeElapsed*50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	translationMatrix = glm::scale(translationMatrix, glm::vec3(0.5f, 0.5f, 0.5f));

}
