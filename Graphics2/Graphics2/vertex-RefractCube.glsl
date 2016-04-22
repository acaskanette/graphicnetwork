#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 FragmentPosition;
out vec3 Normal;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
    FragmentPosition = vec3(modelMatrix * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(modelMatrix))) * normal;       
}