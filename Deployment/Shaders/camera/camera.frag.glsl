#version 420 core

smooth in vec2 tc;
smooth in vec4 outPos;
smooth in float vsBrightness;
out vec4 color;

layout (binding = 0) uniform usamplerBuffer buffer;
layout (binding = 1) uniform sampler2DArray sampler;

uniform float spacing;
uniform int heightMapSize;
uniform int textureMapResolution;

int tcms = (heightMapSize-1) * textureMapResolution + 1;


int centerIndexForPos(vec4 pos)
{
	ivec2 indexPos;
	indexPos.x = int(pos.x / spacing * textureMapResolution);
	indexPos.y = int(pos.z / spacing * textureMapResolution);

	return indexPos.x + indexPos.y*tcms;
}


uint textureIndexForCenterIndex(int index)
{
	return texelFetch(buffer, index).r;
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
	float tms = spacing / textureMapResolution;

	int centerIndex = centerIndexForPos(outPos);

	vec4 topLeft = texelForIndex(textureIndexForCenterIndex(centerIndex));
	vec4 topRight = texelForIndex(textureIndexForCenterIndex(centerIndex+1));
	vec4 bottomLeft = texelForIndex(textureIndexForCenterIndex(centerIndex+tcms));
	vec4 bottomRight = texelForIndex(textureIndexForCenterIndex(centerIndex+tcms+1));

	float integerPart;
	float hLerp = modf(outPos.x/spacing*textureMapResolution, integerPart);
	float vLerp = modf(outPos.z/spacing*textureMapResolution, integerPart);

	vec4 h1 = mix(topLeft, topRight, hLerp);
	vec4 h2 = mix(bottomLeft, bottomRight, hLerp);

	color = mix(h1, h2, vLerp);

	//mix with black to apply lighting
	const vec4 black = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	color = mix(black, color, vsBrightness);
}
