#version 420 core

in vec2 outTexturePos;
uniform sampler2D sampler;
out vec4 color;

void main()
{
	//color = texture(sampler, gl_FragCoord.xy / textureSize(sampler, 0));
	//color = texture(sampler, outTexturePos);

	ivec2 txSize = textureSize(sampler, 0);
	ivec2 pos;
	pos.x = txSize.x - int(outTexturePos.x * txSize.x) - 1;
	pos.y = txSize.y - int(outTexturePos.y * txSize.y) - 1;
	color = texelFetch(sampler, pos, 0);
}