#version 330 core

layout (location = 0) in vec4 pos;

uniform mat4 transformation;

out vec2 outTexturePos;

void main()
{
	gl_Position = transformation * pos;

	outTexturePos = vec2(pos.x, pos.y);
}