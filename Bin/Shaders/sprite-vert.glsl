#version 330 core

layout (location = 0) in vec4 pos;

uniform mat4 transformation;
vec2 subBottomLeft;
vec2 subSize;

out vec2 outTexturePos;

void main()
{
	subBottomLeft = vec2(0.5, 0.5);
	subSize = vec2(0.5, 0.5);

	vec2 subUpRight = subBottomLeft + subSize;

	//clamp to the sub-rect
	vec4 trimmed = vec4(min(max(subBottomLeft.x, pos.x), subUpRight.x),
						min(max(subBottomLeft.y, pos.y), subUpRight.y),
						pos.z,
						pos.w);

	gl_Position = transformation * trimmed;
	outTexturePos = vec2(trimmed.x, trimmed.y);
}