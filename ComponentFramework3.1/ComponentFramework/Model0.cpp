#include "Model0.h"
#include "QuadSphere.h"
#include "Shader.h"
using namespace GAME;

Model0::Model0():quadSphere(nullptr),shader(nullptr) {
	OnCreate();
}

bool Model0::OnCreate(){

	/// Create a cube
	quadSphere = new QuadSphere(3); 


	lightPos = Vec3(10.0, 10.0, 10.0);
	cameraPos = Vec3(0.0, 5.0, 10.0);
	/// Create a shader with attributes
	shader = new Shader("blinnphongVert.glsl","blinnphongFrag.glsl",3,  0,"vVertex",   1,"vNormal",   2,"textCoords");



	#define VERTEX_LENGTH 	(quadSphere->getNumVertices() * (sizeof(Vec4)))
	#define NORMAL_LENGTH 	(quadSphere->getNumVertices() * (sizeof(Vec4)))
	#define TEXCOORD_LENGTH (quadSphere->getNumVertices() * (sizeof(Vec2)))
	


    /// Create and initialize vertex buffer object VBO
    
    glGenBuffers(1, &vbo );
    glBindBuffer(GL_ARRAY_BUFFER, vbo);/// This binds buffer to the target name GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH , NULL, GL_STATIC_DRAW );


	 /// assigns the addr of "points" to be the beginning of the array buffer "sizeof(points)" in length
	glEnableVertexAttribArray(0);
    glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_LENGTH, quadSphere->getVerticies() );
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(0) );


	/// assigns the addr of "normals" to be "sizeof(points)" offset from the beginning and "sizeof(normals)" in length  
	glEnableVertexAttribArray(1);
    glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH, NORMAL_LENGTH, quadSphere->getNormals() );
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(VERTEX_LENGTH) );


	/// assigns the addr of "texCoords" to be "sizeof(points) + sizeof(normals)" offset from the beginning and "sizeof(texCoords)" in length  
	glEnableVertexAttribArray(2);
    glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH , TEXCOORD_LENGTH , quadSphere->getTexCoords());
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(VERTEX_LENGTH + NORMAL_LENGTH) );

	  
	#undef VERTEX_LENGTH
	#undef NORMAL_LENGTH
	#undef TEXCOORD_LENGTH

	projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
	normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
	lightPosID = glGetUniformLocation(shader->getProgram(), "lightPos");
	cameraPosID = glGetUniformLocation(shader->getProgram(), "cameraPos");

	glBindBuffer(GL_ARRAY_BUFFER,0); /// Unbinds the buffer by setting it to zero 
	return true;
}


void Model0::OnDestroy(){
	glDeleteBuffers(1,  &vbo);
}

void Model0::Update(const float deltaTime){

}



void Model0::Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix) const{
	
	glUseProgram(shader->getProgram());
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, modelViewMatrix);
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);
	glUniform3fv(lightPosID, 1, lightPos);
	glUniform3fv(cameraPosID, 1, cameraPos);
	glDrawArrays(GL_QUADS, 0, quadSphere->getNumVertices());
	
}


Model0::~Model0(){
	if(quadSphere) delete quadSphere;
	if(shader) delete shader;
}
