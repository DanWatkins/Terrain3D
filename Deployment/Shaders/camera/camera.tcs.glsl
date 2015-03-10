#version 420 core

//==================================================================================================================|
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

layout (vertices = 4) out;

in VSOut
{
	vec2 tc;
} tcsIn[];

out TCSOut
{
	vec2 tc;
} tcsOut[];

uniform int terrainSize;
uniform int chunkSize;
uniform vec3 cameraPos;

void main()
{
	if (gl_InvocationID == 0)
	{
		const int base = 40;
	
		gl_TessLevelOuter[0] = base;
		gl_TessLevelOuter[1] = base;
		gl_TessLevelOuter[2] = base;
		gl_TessLevelOuter[3] = base;
		
		gl_TessLevelInner[0] = 20;
		gl_TessLevelInner[1] = 20;
	}
	
	
	tcsOut[gl_InvocationID].tc = tcsIn[gl_InvocationID].tc;
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}