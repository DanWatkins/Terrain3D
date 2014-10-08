#version 330 core

in vec4 shaderColor;
smooth in vec2 tc;
out vec4 color;

uniform sampler2D sampler;
uniform float spacing;

void main()
{
	ivec2 txSize = textureSize(sampler, 0);
	ivec2 pos;
	
	pos.x = int(tc.x * txSize);
	pos.y = int(tc.y * txSize);
	
	color = texelFetch(sampler, pos, 0);
}