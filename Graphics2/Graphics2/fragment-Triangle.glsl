#version 330 core

uniform vec4 ourColor;

in vec4 vertexColor;

out vec4 color;

void main()
{
    color = ourColor;
} 