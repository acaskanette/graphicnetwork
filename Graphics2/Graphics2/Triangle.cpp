#include "Triangle.h"
#include <gl\glew.h>

Triangle::Triangle()
{

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

}


Triangle::~Triangle()
{
}
