#ifndef MODEL0_H
#define MODEL0_H
#include <GL/glew.h>
#include "Model.h"

namespace GAME {
class Shader; /// Forward declarations;
class QuadSphere;

class Model0 :public Model {
public:
	Model0();


	Model0(const Model0&) = delete;
	Model0(Model0&&) = delete;
	Model0& operator = (const Model0&) = delete;
	Model0& operator = (Model0&&) = delete;

	virtual bool OnCreate() ;
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix) const;
	virtual ~Model0();

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
