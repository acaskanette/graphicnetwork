#include "Window.h"
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <stdio.h>
#include <string>
#include "Camera.h"

Window::Window()
{
	
}


Window::~Window()
{
	//Deallocate program
	glDeleteProgram(gProgramID);

	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();

}

bool Window::Initialize() {
	
		//Initialization flag
		bool success = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Use OpenGL 3.3 core
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			//Create window
			gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
			if (gWindow == NULL)
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Create context
				gContext = SDL_GL_CreateContext(gWindow);
				if (gContext == NULL)
				{
					printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
				else
				{
					//Initialize GLEW
					glewExperimental = GL_TRUE;
					GLenum glewError = glewInit();
					if (glewError != GLEW_OK)
					{
						printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
					}

					//Use Vsync
					if (SDL_GL_SetSwapInterval(1) < 0)
					{
						printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
					}
					
					// Initialize OpenGL Objects here
					triangle = new Skybox();
					camera = new Camera();

					glEnable(GL_DEPTH_TEST);

				}
			}
		}

		return success;
	
}


bool Window::InitializeGL() {
	
		//Success flag
		bool success = true;

		//Generate program
		gProgramID = glCreateProgram();

		//Create vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		//Get vertex source
		const GLchar* vertexShaderSource[] =
		{
			"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
		};

		//Set vertex source
		glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

		//Compile vertex source
		glCompileShader(vertexShader);

		//Check vertex shader for errors
		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
		if (vShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile vertex shader %d!\n", vertexShader);
			PrintShaderLog(vertexShader);
			success = false;
		}
		else
		{
			//Attach vertex shader to program
			glAttachShader(gProgramID, vertexShader);


			//Create fragment shader
			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			//Get fragment source
			const GLchar* fragmentShaderSource[] =
			{
				"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
			};

			//Set fragment source
			glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

			//Compile fragment source
			glCompileShader(fragmentShader);

			//Check fragment shader for errors
			GLint fShaderCompiled = GL_FALSE;
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
			if (fShaderCompiled != GL_TRUE)
			{
				printf("Unable to compile fragment shader %d!\n", fragmentShader);
				PrintShaderLog(fragmentShader);
				success = false;
			}
			else
			{
				//Attach fragment shader to program
				glAttachShader(gProgramID, fragmentShader);


				//Link program
				glLinkProgram(gProgramID);

				//Check for errors
				GLint programSuccess = GL_TRUE;
				glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
				if (programSuccess != GL_TRUE)
				{
					printf("Error linking program %d!\n", gProgramID);
					PrintProgramLog(gProgramID);
					success = false;
				}
				else
				{
					//Get vertex attribute location
					gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
					if (gVertexPos2DLocation == -1)
					{
						printf("LVertexPos2D is not a valid glsl program variable!\n");
						success = false;
					}
					else
					{
						//Initialize clear color
						glClearColor(0.f, 0.f, 0.f, 1.f);

						//VBO data
						GLfloat vertexData[] =
						{
							-0.5f, -0.5f,
							0.5f, -0.5f,
							0.5f, 0.5f,
							-0.5f, 0.5f
						};

						//IBO data
						GLuint indexData[] = { 0, 1, 2, 3 };

						//Create VBO
						glGenBuffers(1, &gVBO);
						glBindBuffer(GL_ARRAY_BUFFER, gVBO);
						glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

						//Create IBO
						glGenBuffers(1, &gIBO);
						glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
						glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
					}
				}
			}
		}

		return success;
	
}

void Window::HandleInput(unsigned char key, int x, int y)
{
	//Toggle quad

	if (key == 'x')
	{
		SDL_DestroyWindow(gWindow);
	}

	if (key == 'q')
	{
		camera->MoveUp(0.5f);
	}

	if (key == 'e')
	{
		camera->MoveDown(0.5f);
	}

	if (key == 'w')
	{
		camera->MoveForward(0.5f);
	}
	if (key == 'a')
	{
		camera->MoveLeft(0.5f);
	}
	if (key == 's')
	{
		camera->MoveBackward(0.5f);
	}
	if (key == 'd')
	{
		camera->MoveRight(0.5f);
	}



}

void Window::Update() {
	
	camera->Update();
	triangle->Update();

}

void Window::Render() {
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	triangle->Render(camera);


	////Render quad
	//if (gRenderQuad)
	//{
	//	//Bind program
	//	glUseProgram(gProgramID);

	//	//Enable vertex position
	//	glEnableVertexAttribArray(gVertexPos2DLocation);

	//	//Set vertex data
	//	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	//	glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	//	//Set index data and render
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	//	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

	//	//Disable vertex position
	//	glDisableVertexAttribArray(gVertexPos2DLocation);

	//	//Unbind program
	//	glUseProgram(NULL);
	//}

	//Update screen
	SDL_GL_SwapWindow(gWindow);
}

void  Window::PrintProgramLog(GLuint program) {
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}

void Window::PrintShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}