#include "TexturedCube.h"
#include "Camera.h"

TexturedCube::TexturedCube()
{

	//camera = new Camera();

	float screenWidth = 640.0f;
	float screenHeight = 480.0f;

	modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
	projectionMatrix = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);


	translationMatrix = glm::rotate(translationMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	translationMatrix = glm::scale(translationMatrix, glm::vec3(0.5f, 0.5f, 0.5f));

	timeElapsed = 0.0f;

	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);	
	// Texture Co-ordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//Unbind VAO
	glBindVertexArray(0);
	// Compile and bind Shaders to program
	program = LoadShaders("vertex-Triangle.glsl", "fragment-Triangle.glsl");

	transformMatrixLocation = glGetUniformLocation(program, "transformMatrix");
	modelMatrixLocation = glGetUniformLocation(program, "modelMatrix");
	viewMatrixLocation = glGetUniformLocation(program, "viewMatrix");
	projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix");

}


TexturedCube::~TexturedCube()
{
}


void TexturedCube::Render(Camera* camera) {

	GLfloat greenValue = (sin(timeElapsed) / 2) + 0.5;
	GLint vertexColorLocation = glGetUniformLocation(program, "ourColor");

	glUseProgram(program);				// Set active program

	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	glUniformMatrix4fv(transformMatrixLocation, 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->viewMatrix));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(program, "ourTexture0"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(program, "ourTexture1"), 1);

	glBindVertexArray(VAO);				// Set active VAO
	
	// Multiple Cubes
	
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};
	
	for (GLuint i = 0; i < 10; i++)
	{
		glm::mat4 model;
		model = glm::translate(model, cubePositions[i]);
		GLfloat angle = 20.0f * i;
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	// End Multiple Cubes

	//glDrawArrays(GL_TRIANGLES, 0, 36);	// Draw from that VAO
	glBindVertexArray(0);				// Reset active VAO

}

void TexturedCube::Update() {

	timeElapsed += 0.016;

	translationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::translate(translationMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	translationMatrix = glm::rotate(translationMatrix, glm::radians(timeElapsed*50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	translationMatrix = glm::scale(translationMatrix, glm::vec3(1.0f, 1.0f, 1.0f));

	modelMatrix = translationMatrix;

}