#version 430 core
layout(location = 0) in vec4 vPosition;
//layout(location = 1) in vec4 vColor;
//layout(location = 2) in vec2 vUV;

//uniform vec3 VertexColor;
//uniform mat4 RotationMatrix;
//uniform mat4 ProjectionMatrix;
//uniform mat4 CameraViewMatrix;

out vec4 Color;
//out vec2 texCoord;


void main()
{
	//Color = VertexColor;
	Color = vec4(0.8,0.0,0.0,1.0);
	//texCoord = vUV;
	gl_Position = /*ProjectionMatrix * CameraViewMatrix * RotationMatrix * */ vPosition;
}
