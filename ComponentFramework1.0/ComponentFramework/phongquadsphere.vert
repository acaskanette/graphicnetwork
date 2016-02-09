#version 330
layout(location = 0) in  vec4 vPosition;
layout(location = 1) in  vec4 vNormal;
// in  vec4 vColor;

smooth out vec3 vertNormal;
smooth out vec3 lightDir;
out vec3 eyePos;
 
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 cameraViewMatrix;
uniform mat4 normalMatrix;

uniform vec4 lightPos;

void main() {

	// Normals
	vertNormal = mat3(transpose(inverse(modelViewMatrix))) * vNormal.xyz;			/// Rotate the normal to the correct orientation 
	
	// Light
	eyePos = vec3(modelViewMatrix * vPosition);			/// Create the eye vector 
	lightDir = normalize(lightPos.xyz - eyePos.xyz);	/// Create the light direction 
	
	//Position
	gl_Position =  projectionMatrix * cameraViewMatrix * modelViewMatrix * vPosition; 

}