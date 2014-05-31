#version 420 core

layout (location = 0) in vec4 inPos;
layout (location = 1) in vec2 inTexPos;

out vec2 outTexPos;

void main()
{	
	gl_Position = inPos;
	outTexPos = inTexPos;
}