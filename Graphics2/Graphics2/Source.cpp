// GLEW - Extension Wrangler for OpenGL
#define GLEW_STATIC
#include <GL/glew.h>

// SDL - Window manager
#include "SDL.h"

// Helpers
#include <iostream>

int main()
{

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		//std::cout << std::string(SDL_GetError());		
	}

	/// These attributes must be set before the SDL window is created 

	/// You may need to change this to 16 or 32 depending on your graphics card
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);/// Enable Depth Cueing (the Z-buffer) 
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);/// Turn on double buffering with a 24bit Z buffer. 

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


	/// Create the SDL window
	SDL_Rect winRect = SDL_Rect();
	
	SDL_Window* windowPtr = SDL_CreateWindow("Component Framework Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		winRect.w, winRect.h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	if (windowPtr == nullptr) {
		//Debug::Log(EMessageType::FATAL_ERROR, SDL_GetError(), __FILE__, __LINE__);
		return false;
	}

	/// Attach OpenGl to the new Window
	SDL_GLContext glContext = SDL_GL_CreateContext(windowPtr);
	if (glContext == nullptr) {
		//Debug::Log(EMessageType::FATAL_ERROR, SDL_GetError(), __FILE__, __LINE__);
		return false;
	}

	// Initialize Glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Set OpenGL viewport size (x, y, width, height)
	glViewport(0, 0, 800, 600);


	
	return 0;
}