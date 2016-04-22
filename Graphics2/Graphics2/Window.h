#pragma once

#include <SDL.h>
#include <gl\glew.h>

#include "Skybox.h"

class Camera;

class Window
{
public:
	Window();
	~Window();

	// Properties
	// Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	// The window we'll be rendering to
	SDL_Window* gWindow = NULL;
	// OpenGL context
	SDL_GLContext gContext;
	// Render flag
	bool gRenderQuad = true;
	// Graphics program
	GLuint gProgramID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO = 0;
	GLuint gIBO = 0;

	// Scene Objects
	Skybox* triangle;
	Camera* camera;

	// Methods

	//Starts up SDL, creates window, and initializes OpenGL
	bool Initialize();

	//Initializes rendering program and clear color
	bool InitializeGL();

	//Input handler
	void HandleInput(unsigned char key, int x, int y);

	//Per frame update
	void Update();

	//Renders quad to the screen
	void Render();

	//Frees media and shuts down SDL
	void Close();

	//Shader loading utility programs
	void PrintProgramLog(GLuint program);
	void PrintShaderLog(GLuint shader);
	
};

