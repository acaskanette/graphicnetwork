#include "GL/glew.h"
#include <SDL.h>
#include "Scene0.h"
#include <iostream>
using namespace GAME;

Scene0::Scene0(class Window& windowRef):  Scene(windowRef) { }

Scene0::~Scene0(){ }

bool Scene0::OnCreate() {
	
	OnResize(windowPtr->GetWidth(), windowPtr->GetHeight());
	/// Load Assets: as needed 


	
	
	return true;
}

void Scene0::OnDestroy(){
	/// Cleanup Assets

}

void Scene0::Update(const float deltaTime){


}

void Scene0::Render() const{
	
	/// Draw your scene here
	 glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// // Old OpenGL
	// glRotatef(2.0f, 1.0f, 0.0f, 1.0f);

	// glBegin(GL_QUADS);
	//	 glColor3f(1.0, 0.0, 0.0);
	//	 glVertex2f(-0.5f, -0.5f);

	//	 glColor3f(0.0, 1.0, 1.0);
	//	 glVertex2f(0.5f, -0.5f);

	//	 glColor3f(1.0, 0.0, 1.0);
	//	 glVertex2f(0.5f, 0.5f);

	//	 glColor3f(1.0, 1.0, 0.0);
	//	 glVertex2f(-0.5f, 0.5f);
	//glEnd();

	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
}

void Scene0::HandleEvents(const SDL_Event& SDLEvent){
	///std::cout << "event!!" << std::endl;
}

void Scene0::OnResize(const int width_, const int height_){
	///std::cout << "event!!" << std::endl;
	windowPtr->SetWindowSize(width_, height_);
	glViewport(0, 0, windowPtr->GetWidth(), windowPtr->GetHeight());
	
	//// Deprecated old OpenGL
	//// Creating Normalized Device Co-Ordinates, make center 0,0, corners -1,-1 (bottom left) to 1,1 (upper right)
	//glMatrixMode(GL_PROJECTION); // deprecated old openGL
	//glLoadIdentity();			 // make the stack matrix the identity matrix
	//glOrtho(0, 10.0, 0.0, 10.0, -1.0, 1.0);	// set up orthographic projection
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glTranslatef(5.0, 5.0, 0.0);
	//glScalef(2.5f, 2.5f, 2.5f);

}