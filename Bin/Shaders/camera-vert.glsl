#version 420 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 color;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;

out vec4 shaderColor;

void main()
{	
	float height = position.y;

	shaderColor = vec4(color.r, color.g, color.b, 1.0f);

	vec4 newPos = vec4(position.x, position.y, position.z, position.w);
	gl_Position = cameraMatrix * modelMatrix * newPos;
}