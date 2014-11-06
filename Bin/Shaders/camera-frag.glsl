#version 420 core

smooth in vec2 tc;
smooth in vec4 outPos;
out vec4 color;

layout (binding = 0) uniform usamplerBuffer buffer;
layout (binding = 1) uniform sampler2DArray sampler;

uniform float spacing;
uniform int heightMapSize;


uint textureIndexForPos(vec4 pos)
{
	ivec2 indexPos;
	indexPos.x = int(pos.x / spacing);
	indexPos.y = int(pos.z / spacing);

	int centerIndex = indexPos.x + indexPos.y*heightMapSize;
	return texelFetch(buffer, centerIndex).r;
}


vec4 texelForIndex(uint index)
{
	vec3 pos;
	pos.x = tc.x;
	pos.y = tc.y;
	pos.z = index;

	return texture(sampler, pos);
}


void main()
{
	color = texelForIndex(textureIndexForPos(outPos));
}
