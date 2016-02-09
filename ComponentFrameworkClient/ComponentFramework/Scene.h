#ifndef SCENE_H
#define SCENE_H

#include "SDL.h"
#include "Window.h"
#include "GL/glew.h"
#include <string>

namespace GAME {
	class Scene {
	public:
		explicit Scene(class Window& windowRef);
		~Scene();

		// Prevents compiler from making weird (copy) constructors
		Scene(const Scene&) = delete;
		Scene(Scene&&) = delete;
		Scene& operator = (const Scene&) = delete;
		Scene& operator = (Scene&&) = delete;
		
		

		/// Create the following four abstract functions and make them polymorphic
		/// The proper term for these are "pure viruals"
		virtual bool OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void Update(const float deltaTime) = 0;
		virtual void Render() const = 0;
		virtual void HandleEvents(const SDL_Event &SDLEvent) = 0;
		virtual void OnResize(const int, const int) = 0;

		virtual GLuint LoadVertShader(const std::string& _filename) = 0;
		virtual GLuint LoadFragShader(const std::string& _filename) = 0;

		virtual GLuint GetProgram() = 0;

	protected:
		Window* windowPtr;
		GLuint program;

	};
}

#endif