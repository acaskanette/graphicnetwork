#include "QuadSphere.h"


QuadSphere::~QuadSphere() {

}

QuadSphere::QuadSphere(int numSubDivisions, GLuint program) {


	projectionLocation = glGetUniformLocation(program, "projectionMatrix");
	modelViewLocation = glGetUniformLocation(program, "modelViewMatrix");
	cameraViewMatrixLocation = glGetUniformLocation(program, "cameraViewMatrix");
	normalLocation = glGetUniformLocation(program, "normalMatrix");
	lightPositionLocation = glGetUniformLocation(program, "lightPos");

	numVertices = 6 * int(::pow(4.0, numSubDivisions + 1 ) );
	index = 0;
	vertex = new Vec4[numVertices];
	normals = new Vec4[numVertices];
	texCoords = new Vec2[numVertices];

	// OnCreate();

	Vec4 cube[8] = {
		///Front 4
		Vec4( -0.5, -0.5,  0.5, 1.0 ),/// Left bottom
		Vec4( -0.5,  0.5,  0.5, 1.0 ),/// Left top
		Vec4(  0.5,  0.5,  0.5, 1.0 ),/// Right top
		Vec4(  0.5, -0.5,  0.5, 1.0 ),/// Right bottom
		///Back 4
		Vec4( -0.5, -0.5, -0.5, 1.0 ),
		Vec4( -0.5,  0.5, -0.5, 1.0 ),
		Vec4(  0.5,  0.5, -0.5, 1.0 ),
		Vec4(  0.5, -0.5, -0.5, 1.0 )
	};

	int count = numSubDivisions;
	if (count > 0){
		for(int j = 0; j<8;++j){
			cube[j] = VMath::normalize(cube[j]);
		}
	}

	/// I'm using the GL_QUADS method of drawing so I'll need specify cube 1234
	DivideFace( cube[1], cube[0], cube[3], cube[2], count); /// Front face
	DivideFace( cube[2], cube[3], cube[7], cube[6], count); /// Right face
	DivideFace( cube[3], cube[0], cube[4], cube[7], count); /// Bottom face
	DivideFace( cube[6], cube[5], cube[1], cube[2], count); /// Top face
	DivideFace( cube[4], cube[5], cube[6], cube[7], count); /// Back face
	DivideFace( cube[5], cube[4], cube[0], cube[1], count); /// Left face

	SphericalNormals();

	/// Might not want to do this here!!! We'll talk in class
	printf("%d vs %d\n",index,numVertices);
	// Create a vertex array object VAO
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); 

#define VERTEX_LENGTH 	(numVertices * (sizeof(Vec4)))
#define NORMAL_LENGTH 	(numVertices * (sizeof(Vec4)))
#define TEXCOORD_LENGTH (numVertices * (sizeof(Vec2)))

    /// Create and initialize vertex buffer object VBO
    GLuint buffer;
    glGenBuffers(1, &buffer );
    glBindBuffer(GL_ARRAY_BUFFER, buffer); /// This binds buffer to the target name GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH , NULL, GL_STATIC_DRAW );


	 /// assigns the addr of "points" to be the beginning of the array buffer "sizeof(points)" in length
	glEnableVertexAttribArray(VERTEX_ATTRIB);
	glBindAttribLocation(program, 0, "vPosition");
    glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_LENGTH, vertex );
	glVertexAttribPointer(VERTEX_ATTRIB, 4, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(0) );


	/// assigns the addr of "normals" to be "sizeof(points)" offset from the beginning and "sizeof(normals)" in length  
	glEnableVertexAttribArray(NORMAL_ATTRIB);
	glBindAttribLocation(program, 0, "vNormal");
    glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH, NORMAL_LENGTH, normals );
	glVertexAttribPointer(NORMAL_ATTRIB, 4, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(VERTEX_LENGTH) );


	/// assigns the addr of "texCoords" to be "sizeof(points) + sizeof(normals)" offset from the beginning and "sizeof(texCoords)" in length  
	glEnableVertexAttribArray(TEXTURE_COORD_ATTRIB);
    glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH , TEXCOORD_LENGTH , texCoords);
	glVertexAttribPointer(TEXTURE_COORD_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(VERTEX_LENGTH + NORMAL_LENGTH) );


#undef VERTEX_LENGTH
#undef NORMAL_LENGTH
#undef TEXCOORD_LENGTH
	/// Set up vertex arrays for the vertex and color attributes
	/// These calls where in the vertex buffer the data is and how to move through it
	/// VERTEX_ATTRIB is the location, 4 is the length of each Vec of type GL_FLOAT, do not normalize, 
	/// the stride is zero and the beginning is zero (pointed to by the addr of a temp stack variable holding the value 0) - weird  
	/// pretty much the same as above but it starts at the end of the "points" array in bytes (pointed to by the addr of a temp stack variable)
	/// same as above but it starts at the end of the "points" array  + the "normal" array in bytes (pointed to by the addr of a temp stack variable)
}


///  LoadFace generates one quad for each face and assigns colors to the vertices
void QuadSphere::LoadFace(const Vec4& a, const Vec4& b, const Vec4& c, const Vec4& d){
	
	Vec4 u = b - a;
	Vec4 v = c - b;
	Vec4 normal = VMath::normalize(VMath::cross(u,v));
	
	normals[index] = normal;  
	vertex[index] = a;
	texCoords[index][0] = 0.0; texCoords[index][1] = 0.0;
	index++;

	normals[index] = normal;
	vertex[index] = b;
	texCoords[index][0] = 0.0; texCoords[index][1] = 1.0;
	index++;

	normals[index] = normal;
	vertex[index] = c;
	texCoords[index][0] = 1.0; texCoords[index][1] = 1.0;
	index++;


	normals[index] = normal;
	vertex[index] = d;
	texCoords[index][0] = 1.0; texCoords[index][1] = 0.0;
	index++;
}


void QuadSphere::DivideFace(const Vec4& a, const Vec4& b, const Vec4& c, const Vec4& d, int count ) {
	if(count > 0){
		Vec4 v1 = VMath::normalize(a + b);
		Vec4 v2 = VMath::normalize(b + c);
		Vec4 v3 = VMath::normalize(c + d);
		Vec4 v4 = VMath::normalize(d + a);
		Vec4 vc = VMath::normalize(a + c);
		DivideFace(a,v1,vc,v4, count-1);
		DivideFace(v1,b,v2,vc, count-1);
		DivideFace(vc,v2,c,v3, count-1);
		DivideFace(v4,vc,v3,d, count-1);
	}else{
		LoadFace(a, b, c, d);
	}
}
/// Since the centre of the sphere is at the origin, the vector formed from the origin to the surface vertex of the sphere
/// (once normalized) would be the normal to a spheres surface - not to the face of the polygon on that sphere! Now it looks smooth. 
void QuadSphere::SphericalNormals(){
	for (int j = 0; j < numVertices; ++j){
		normals[j] = VMath::normalize(vertex[j]);
	}
}


bool QuadSphere::OnCreate() {
	return true;
}

void QuadSphere::OnDestroy() {
	
}

void QuadSphere::Update(const float deltaTime) {
	
}

void QuadSphere::Render() const {

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 rotationTranslationMatrix = glm::rotate(translationMatrix, 0.0f, glm::vec3(0, 0, 1));

	glm::mat4 projectionMatrix = glm::perspective(45.0f, 1024.0f / 1024.0f, 0.1f, 200.f); // vertical opening angle, ratio of vertical opening to horizontal, distance between camera and near plane (don't use zero), distance between camera to the far plane

	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -10.0f);
	glm::vec3 cameraFacing = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUpVector = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 cameraViewMatrix = glm::lookAt(cameraPosition,		// position of camera,
		cameraFacing,			// direction camera is facing,
		cameraUpVector);		// camera's up vector

	glm::mat4 normalMatrix = rotationTranslationMatrix;

	glm::vec4 lightPosition = glm::vec4(5.0f,5.0f,0.0f, 0.0f);

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);				// send matrix to shader
	glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &rotationTranslationMatrix[0][0]);   // send matrix to shader
	glUniformMatrix4fv(cameraViewMatrixLocation, 1, GL_FALSE, &cameraViewMatrix[0][0]);				// send matrix to shader	
	glUniformMatrix4fv(normalLocation, 1, GL_FALSE, &normalMatrix[0][0]);				// send matrix to shader	

	glUniform4fv(lightPositionLocation, 1, &lightPosition[0]);
	

	glDrawArrays(GL_QUADS, 0, numVertices);

}
	













