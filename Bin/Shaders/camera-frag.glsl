#version 420 core

smooth in vec2 tc;
smooth in vec4 outPos;
out vec4 color;

layout (binding = 0) uniform usamplerBuffer buffer;
layout (binding = 1) uniform sampler2DArray sampler;

uniform float spacing;
uniform int heightMapSize;

void main()
{
	vec3 pos;
	pos.x = tc.x;
	pos.y = tc.y;

	//determine the terrain layer
	{
		ivec2 indexPos;
		indexPos.x = int(outPos.x / spacing);
		indexPos.y = int(outPos.z / spacing);

		int index = indexPos.x + indexPos.y*heightMapSize;
		pos.z = texelFetch(buffer, index).r;
	}

	color = texture(sampler, pos);
}
