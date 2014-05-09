#version 420 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 color;

uniform mat4 translationMat;

out vec4 shaderColor;

void main()
{
	gl_Position = translationMat * position;

	shaderColor = vec4(color.y, color.y, color.y, 1.0f);
}