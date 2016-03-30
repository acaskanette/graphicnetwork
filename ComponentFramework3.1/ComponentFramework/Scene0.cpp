#include "GL/glew.h"
#include <SDL.h>
#include "Scene0.h"
#include <iostream>
#include "MMath.h"
#include "QuadSphere.h"
#include "Model0.h"
#include "TexturedCube.h"

using namespace GAME;

Scene0::Scene0(class Window& windowRef):  Scene(windowRef), cube(nullptr) { 
	projectionMatrix.loadIdentity();
	modelViewMatrix.loadIdentity();
	normalMatrix.loadIdentity();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
}

Scene0::~Scene0(){ 
	OnDestroy();
}

bool Scene0::OnCreate() {
	OnResize(windowPtr->GetWidth(),windowPtr->GetHeight());

	/// Load Assets: as needed 
	cube = new TexturedCube();
	trackball = new Trackball();
	updateTrackball = false;
	return true;
}


void Scene0::OnResize(int w_, int h_){
	windowPtr->SetWindowSize(w_,h_);
	glViewport(0,0,windowPtr->GetWidth(),windowPtr->GetHeight());
	float aspect = float(windowPtr->GetWidth()) / float(windowPtr->GetHeight());
	
	projectionMatrix = MMath::perspective(45.0f, aspect, 1.0f, 100.0f);
	modelViewMatrix = MMath::lookAt(Vec3(0.0f, 5.0f, 10.0f), 
									Vec3(0.0f, 0.0f, 0.0f), 
									Vec3(0.0f, 1.0f, 0.0f));
	
}

void Scene0::OnDestroy(){

	/// Cleanup Assets
	if(cube) delete cube;
	cube = nullptr;
}

void Scene0::Update(const float deltaTime){
	
	if (updateTrackball)
		modelViewMatrix = trackball->mouseRotationMatrix * modelViewMatrix ;

}

void Scene0::Render() const{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cube->Render(projectionMatrix,modelViewMatrix, normalMatrix);
	
	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
}

void Scene0::HandleEvents(const SDL_Event& SDLEvent){

	switch (SDLEvent.type) {	
	case SDL_EventType::SDL_MOUSEBUTTONDOWN:				
		trackball->OnLeftMouseButtonDown(SDLEvent.button.x, SDLEvent.button.y);
		updateTrackball = true;
		break;
	case SDL_EventType::SDL_MOUSEBUTTONUP:
		updateTrackball = false;
		break;
	case SDL_EventType::SDL_MOUSEMOTION:	
		if (updateTrackball)
			trackball->OnMouseMove(SDLEvent.button.x,SDLEvent.button.y);
		break;	
	default:
		break;
	}

	///std::cout << "event!!" << std::endl;
}