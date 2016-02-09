/// A simple subdivided cube - SSF
#include "VMath.h"
#include "MMath.h"
#include "SceneObject.h"
#include <gl\glew.h>

using namespace MATH;

class QuadSphere: public SceneObject {
private:
	int numVertices;
	int index;
	Vec4 *vertex;
	Vec4 *normals;
	Vec2 *texCoords;
		

	GLfloat modelViewLocation;
	GLfloat projectionLocation;
	GLfloat normalLocation;
	GLfloat cameraViewMatrixLocation;
	GLfloat lightPositionLocation;

	GLuint vao;

	enum ATTRIB_LOCATIONS {
		VERTEX_ATTRIB, NORMAL_ATTRIB, TEXTURE_COORD_ATTRIB
	};

	void LoadFace(const Vec4& a, const Vec4& b, const Vec4& c, const Vec4& d);
	void DivideFace(const Vec4& a, const Vec4& b, const Vec4& c, const Vec4& d, int count);
	void SphericalNormals();
	
public:
	
	QuadSphere(int numSubDivisions, GLuint program);
	~QuadSphere();
	
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;

};



