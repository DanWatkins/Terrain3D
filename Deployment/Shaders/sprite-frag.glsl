#version 330 core

in vec2 outTexturePos;
uniform sampler2D sampler;
out vec4 color;

void main()
{
	ivec2 txSize = textureSize(sampler, 0);
	ivec2 pos;

	pos.x = int(outTexturePos.x * txSize.x);
	pos.y = int(outTexturePos.y * txSize.y);
	
	color = texelFetch(sampler, pos, 0);
}