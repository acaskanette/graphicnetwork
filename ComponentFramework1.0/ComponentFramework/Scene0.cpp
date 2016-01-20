#include <SDL.h>
#include "Scene0.h"
#include <iostream>
#include <fstream>
using namespace GAME;

Scene0::Scene0(class Window& windowRef):  Scene(windowRef) { }

Scene0::~Scene0(){ }

bool Scene0::OnCreate() {

	OnResize(windowPtr->GetWidth(), windowPtr->GetHeight());
	/// Load Assets: as needed 

	program = 0;

	// Load a program and link the shaders to it
	program = glCreateProgram();
	GLuint vertexShader = LoadVertShader("shader.vert");
	glAttachShader(program, vertexShader);
	GLuint fragmentShader = LoadFragShader("shader.frag");
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	// Check if the program was linked properly before...
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

	// If it's not linked properly, log the error
	if (isLinked == GL_FALSE) {
		// Get the infolog regarding the failure
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		
		// Clear memory, since we don't need these anymore
		glDeleteProgram(program);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return false;
		
	}
	else {	// Otherwise, we're linked up, so:

		//glEnable(GL_DEPTH_TEST);

		// Use this program
		glUseProgram(program);
		// Get rid of the references we don't need anymore
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);		

		return true;
	}


	// Make a Sphere
	testObject = new QuadSphere(4);

}

GLuint Scene0::LoadVertShader(const std::string& _filename) {

	//Open File
	GLuint shader = 0;
	std::ifstream sourceFile(_filename.c_str());

	//Check if file loaded properly
	if (sourceFile) {
		// Create the shader, load and compile it
		std::string shaderString;
		shaderString.assign((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
		shader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* shaderSource = shaderString.c_str();
		glShaderSource(shader, 1, (const GLchar**)&shaderSource, NULL);
		glCompileShader(shader);

		// Check if compiled properly
		GLint shaderCompiled = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
		// If it didn't, log the error and save some memory
		if (shaderCompiled != GL_TRUE) {
			//LogManager::GetInstance().LogError("Unable to compile shader" + std::to_string(shader) + "  Source: " + shaderSource + "/n");
			glDeleteShader(shader);
			shader = 0;
		}
	}

	return shader;

}


GLuint Scene0::LoadFragShader(const std::string& _filename) {

	//Open File
	GLuint shader = 0;
	std::ifstream sourceFile(_filename.c_str());

	//Check if file loaded properly
	if (sourceFile) {
		// Create the shader, load and compile it
		std::string shaderString;
		shaderString.assign((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* shaderSource = shaderString.c_str();
		glShaderSource(shader, 1, (const GLchar**)&shaderSource, NULL);
		glCompileShader(shader);

		// Check if compiled properly
		GLint shaderCompiled = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
		// If it didn't, log the error and save some memory
		if (shaderCompiled != GL_TRUE) {
			//LogManager::GetInstance().LogError("Unable to compile shader" + std::to_string(shader) + "  Source: " + shaderSource + "/n");
			glDeleteShader(shader);
			shader = 0;
		}
	}

	return shader;

}


void Scene0::OnDestroy(){
	// Cleanup Assets

}

void Scene0::Update(const float deltaTime){

	// Update the sphere
	testObject->Update(deltaTime);

}

void Scene0::Render() const{
	
	/// Draw your scene here
	 glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Render the sphere
	 testObject->Render();

	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
}

void Scene0::HandleEvents(const SDL_Event& SDLEvent){
	///std::cout << "event!!" << std::endl;
}

void Scene0::OnResize(const int width_, const int height_){
	///std::cout << "event!!" << std::endl;
	windowPtr->SetWindowSize(width_, height_);
	glViewport(0, 0, windowPtr->GetWidth(), windowPtr->GetHeight());	

}