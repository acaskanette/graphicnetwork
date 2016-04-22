#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 TexCoords;

void main()
{
	vec4 pos = projectionMatrix * viewMatrix * vec4(position, 1.0f);
    gl_Position = pos.xyww;
    TexCoords = position; 
}