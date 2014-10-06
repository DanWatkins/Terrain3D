#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 color;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;
uniform float heightScale = 10.0f;

out vec4 shaderColor;
out vec4 outPosition;

void main()
{	
	shaderColor = vec4(color.r, color.g, color.b, 1.0f);

	vec4 scaledPosition = vec4(position.x, position.y*heightScale, position.z, position.w);
	outPosition = scaledPosition;

	gl_Position = cameraMatrix * modelMatrix * scaledPosition;
}