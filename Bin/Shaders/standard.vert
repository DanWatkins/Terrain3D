#version 420 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 color;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;

out vec4 shaderColor;

void main()
{
	gl_Position = cameraMatrix * modelMatrix * position;

	float color = position.y;
	shaderColor = vec4(color, color, color, 1.0f);
}