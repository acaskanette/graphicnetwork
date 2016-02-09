#version 430 core

in vec4 Color;
in vec4 Normal;
//in vec2 texCoord;

//uniform sampler2D texture;
out vec4 fColor;

void main()
{


	fColor = Color;
	
	// For Textures:
	// fColor =  texture2D(texture, texCoord);
}