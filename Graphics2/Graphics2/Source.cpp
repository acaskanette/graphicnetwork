/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL OpenGL, GLEW, standard IO, and strings
#include <SDL.h>
//#include <gl\glew.h>
//#include <SDL_opengl.h>
//#include <gl\glu.h>
#include <stdio.h>
#include <string>

#include "Window.h"

int main(int argc, char* args[])
{
	Window* window = new Window();

	//Start up SDL and create window
	if (!window->Initialize())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//Enable text input
		SDL_StartTextInput();

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				//Handle keypress with current mouse position
				else if (e.type == SDL_TEXTINPUT)
				{
					int x = 0, y = 0;
					SDL_GetMouseState(&x, &y);
					window->HandleInput(e.text.text[0], x, y);
				}
			}

			


			// Update Window
			window->Update();

			//Render Window
			window->Render();

			
		}

		//Disable text input
		SDL_StopTextInput();
	}

	//Free resources and close SDL
	delete window;

	return 0;
}