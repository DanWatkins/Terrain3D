#version 420 core

layout (location = 0) in vec4 pos;

uniform vec4 scale;
uniform vec4 offset;

out vec2 outTexturePos;

void main()
{
	gl_Position = pos * scale + offset;

	outTexturePos = vec2(pos.x, pos.y);
}