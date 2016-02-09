#version 330
in vec4 vVertex;
in vec4 vNormal;
in vec4 vColor;
 
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform vec3 lightPos;
uniform vec3 cameraPos;

out vec3 vertNormal;
out vec3 lightDir;
out vec3 cameraDir;
//out vec2 texcoords;

void main() {
	
	// Normal
	vertNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	// World Position
	vec4 eyePos = modelViewMatrix * vVertex; /// Create the eye vector 
	// Light
	lightDir = normalize(lightPos - eyePos.xyz); /// Create the light direction 
	// Camera
	cameraDir = normalize(cameraPos - eyePos.xyz); // Create CameraPosition
	// Position
	gl_Position =  projectionMatrix * modelViewMatrix * vVertex; 

}
