#version 420 core

smooth in vec2 tc;
out vec4 color;

layout (binding = 0) uniform usamplerBuffer buffer;
layout (binding = 1) uniform sampler2DArray sampler;
uniform float spacing;


void main()
{
	vec3 pos;
	pos.x = tc.x;
	pos.y = tc.y;

	pos.z = texelFetch(buffer, 0).r;


	color = texture(sampler, pos);
}
