#version 330 core

in vec4 shaderColor;
in vec4 outPosition;

out vec4 color;

uniform sampler2D sampler;
uniform float spacing = 0.1;

void main()
{
	int x = bool((int(outPosition.x / spacing) % 2)) ? 0 : 1;
	int y = bool((int(outPosition.z / spacing) % 2)) ? 0 : 1;
	ivec2 texPos = ivec2(x, y);


	vec4 textureColor = texelFetch(sampler, texPos, 0);;

	color = mix(shaderColor, textureColor, 0.05);
}