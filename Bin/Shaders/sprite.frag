#version 420 core

uniform sampler2d tex;
in vec2 vsTexPos;
out vec4 color;


void main()
{
	color = texture(tex, vsTexPos);;
}