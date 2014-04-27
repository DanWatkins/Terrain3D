#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform vec4 aspectScale;
uniform vec4 offset;
uniform float rotation;

out vec4 shaderColor;

void main()
{
	mat4 rotationMatrix = mat4(	cos(rotation),	-sin(rotation),		0.0,	0.0,
								sin(rotation),	cos(rotation),		0.0,	0.0,
								0.0,			0.0,				1.0,	0.0,
								0.0,			0.0,				0.0,	1.0);
	
	gl_Position = ((rotationMatrix * position) + offset) * aspectScale;
	shaderColor = color;
}