#version 420 core

uniform sampler2D sampler;
out vec4 color;

void main()
{
	color = texture(sampler, gl_FragCoord.xy / textureSize(sampler, 0));
}