#version 420 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 color;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;

out vec4 shaderColor;

void main()
{
	gl_Position = cameraMatrix * modelMatrix * position;

	vec4 color;
	float height = position.y;

	if (height > 0.9)
		color = vec4(0.7f, 0.7f, 0.7f, 1.0f);
	else if (height > 0.8)
		color = vec4(0.5, 0.6f, 0.5, 1.0f);
	else if (height > 0.7)
		color = vec4(0.1f, 0.35f, 0.0f, 1.0f);
	else if (height > 0.6)
		color = vec4(0.0f, 0.5f, 0.0f, 1.0f);
	else if (height > 0.5)
		color = vec4(0.6f, 0.35f, 0.1f, 1.0f);
	else if (height > 0.4)
		color = vec4(0.0f, .0f, 0.6, 1.0f);
	else if (height > 0.3)
		color = vec4(0.0f, 0.0f, 0.6, 1.0f);
	else if (height > 0.2)
		color = vec4(0.6f, 0.35f, 0.1f, 1.0f);
	else if (height > 0.1)
		color = vec4(0.0f, 0.0f, 0.0f, 1.0f);


	shaderColor = color;
}