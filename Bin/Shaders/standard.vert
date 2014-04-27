#version 430 core

layout (location = 0) in vec4 position;

out vec4 shaderColor;

void main()
{
	gl_Position = position;
	shaderColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
}