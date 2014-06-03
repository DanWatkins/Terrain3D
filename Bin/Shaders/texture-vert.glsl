#version 420 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 texturePos;

out vec2 outTexturePos;

void main()
{	
	gl_Position = pos;

	outTexturePos = vec2(texturePos.x, texturePos.y);
}