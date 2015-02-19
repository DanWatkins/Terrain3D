#version 430 core

layout (vertices = 4) out;

in VSOut
{
	vec2 heightTc;
} tcsIn[];

out TCSOut
{
	vec2 heightTc;
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
	
	
	tcsOut[gl_InvocationID].heightTc = tcsIn[gl_InvocationID].heightTc;
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}