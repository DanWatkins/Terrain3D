//==================================================================================================================|
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#version 420 core

layout (vertices = 4) out;

in VSOut
{
	vec2 tc;
} tcsIn[];

out TCSOut
{
	vec2 tc;
} tcsOut[];


void main()
{
	if (gl_InvocationID == 0)
	{
		const int base = 3;
	
		gl_TessLevelOuter[0] = base;
		gl_TessLevelOuter[1] = base;
		gl_TessLevelOuter[2] = base;
		gl_TessLevelOuter[3] = base;
		
		gl_TessLevelInner[0] = base;
		gl_TessLevelInner[1] = base;
	}
	
	
	tcsOut[gl_InvocationID].tc = tcsIn[gl_InvocationID].tc;
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}