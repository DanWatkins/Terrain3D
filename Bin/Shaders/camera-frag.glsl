#version 430 core

smooth in vec2 tc;
out vec4 color;

uniform sampler2DArray sampler;
uniform float spacing;


void main()
{
	vec3 pos;
	pos.x = tc.x;
	pos.y = tc.y;
	pos.z = 0;

	color = texture(sampler, pos);
}
