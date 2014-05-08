#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec4 shaderColor;

void main()
{
	gl_Position = vec4(position, 1.0f);

	shaderColor = vec4(color.x, color.y, color.z, 1.0f);
}