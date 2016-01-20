#ifndef Scene0_H
#define Scene0_H

#include "Scene.h"
#include "Window.h"
#include "Quadsphere.h"

namespace GAME {
	class Scene0 : public Scene  {
	
	protected:

		SceneObject* testObject;
		
	public:
		explicit Scene0(Window& windowRef);
		virtual ~Scene0();


		/// Delete these possible default constructors and operators  
		Scene0(const Scene0&) = delete;
		Scene0(Scene0 &&) = delete;
		Scene0& operator=(const Scene0 &) = delete;
		Scene0& operator=(Scene0 &&) = delete;

		virtual bool OnCreate() ;
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render() const;
		virtual void HandleEvents(const SDL_Event &SDLEvent);
		virtual void OnResize(const int width, const int height);

		virtual GLuint LoadVertShader(const std::string& _filename);
		virtual GLuint LoadFragShader(const std::string& _filename);

	};
}
#endif