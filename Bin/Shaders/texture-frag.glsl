#version 420 core

in vec2 outTexturePos;
uniform sampler2D sampler;
out vec4 color;

void main()
{
	//color = texture(sampler, gl_FragCoord.xy / textureSize(sampler, 0));
	//color = texture(sampler, outTexturePos);

	ivec2 pos;
	pos.x = int(outTexturePos.x * textureSize(sampler, 0).x);
	pos.y = int(outTexturePos.y * textureSize(sampler, 0).y);
	color = texelFetch(sampler, pos, 0);
}