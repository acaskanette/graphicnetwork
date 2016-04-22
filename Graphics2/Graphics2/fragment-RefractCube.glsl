#version 330 core

in vec3 Normal;
in vec3 FragmentPosition;

out vec4 color;

uniform vec3 cameraPosition;
uniform samplerCube skybox;

void main()
{    
	vec3 I = normalize(FragmentPosition - cameraPosition);
	vec3 R = reflect(I, normalize(Normal));
	//color = texture(skybox, R);
	color = vec4(1.0,1.0,1.0,1.0);
}