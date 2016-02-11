#ifndef TEXTURED_CUBE_H
#define MODEL0_H
#include <GL/glew.h>
#include "Model.h"

namespace GAME {
	class Shader; /// Forward declarations;
	class QuadSphere;

	class TexturedCube :public Model {
	public:

		TexturedCube();

		TexturedCube(const TexturedCube&) = delete;
		TexturedCube(TexturedCube&&) = delete;
		TexturedCube& operator = (const TexturedCube&) = delete;
		TexturedCube& operator = (TexturedCube&&) = delete;

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix) const;
		virtual ~TexturedCube();

	private:
		QuadSphere *quadSphere;
		Shader *shader;
		GLuint vbo;
		Vec3 lightPos;
		Vec3 cameraPos;
		GLuint projectionMatrixID;
		GLuint modelViewMatrixID;
		GLuint normalMatrixID;
		GLuint lightPosID;
		GLuint cameraPosID;
	};
}
#endif
