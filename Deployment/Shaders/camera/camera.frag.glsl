#version 420 core

//==================================================================================================================|
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

in TESOut
{
	vec2 tc;
	vec3 worldCoord;
	vec3 eyeCoord;
} fsIn;

out vec4 color;

uniform float height;

layout (binding = 1) uniform usamplerBuffer buffer;
layout (binding = 2) uniform sampler2DArray sampler;

uniform int terrainSize;
uniform float spacing;
uniform int heightMapSize;
uniform int textureMapResolution;


vec4 texelForIndex(uint index)
{
	vec3 pos;
	pos.x = fsIn.tc.x * 8.0;
	pos.y = fsIn.tc.y * 8.0;
	pos.z = index;

	return texture(sampler, pos);
}


void main()
{
	int tcms = (heightMapSize-1) * textureMapResolution + 1;

	int x = int(fsIn.tc.x * tcms);
	int y = int(fsIn.tc.y * tcms);
	int index = x + y*tcms;

	color = texelForIndex(texelFetch(buffer, index).r);
}