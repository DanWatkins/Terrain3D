#version 330 core

in vec4 shaderColor;
in vec4 outPosition;
in vec2 tc;
out vec4 color;

uniform sampler2D sampler;
uniform float spacing;

void main()
{
	//int x = bool((int(outPosition.x / spacing) % 2)) ? 0 : 1;
	//int y = bool((int(outPosition.z / spacing) % 2)) ? 0 : 1;
	/*
	int x = int(mod(outPosition.x / 1.0, spacing));
	int y = int(mod(outPosition.z / 1.0, 700.0));
	
	ivec2 texPos = ivec2(x, y);


	//vec4 textureColor = texelFetch(sampler, texPos, 0);;

	vec4 textureColor = texelFetch(sampler, texPos, 0);
	color = mix(shaderColor, textureColor, 1.0);*/
	
	
	ivec2 txSize = textureSize(sampler, 0);
	ivec2 pos;
	
	pos.x = int(tc.x * txSize);
	pos.y = 0;
	
	color = texelFetch(sampler, pos, 0);
}