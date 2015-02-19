#version 430 core

layout (quads, fractional_odd_spacing) in;

in TCSOut
{
	vec2 heightTc;
} tesIn[];


out TESOut
{
	vec2 heightTc;
	vec3 worldCoord;
	vec3 eyeCoord;
} tesOut;

uniform mat4 mvMatrix;
uniform mat4 projMatrix;
uniform float height;

layout (binding = 0) uniform sampler2D heightMapSampler;


void main()
{
	//interpolate the 4 height map coordinates
	vec2 tc1 = mix(tesIn[0].heightTc, tesIn[1].heightTc, gl_TessCoord.x);
	vec2 tc2 = mix(tesIn[2].heightTc, tesIn[3].heightTc, gl_TessCoord.x);
	vec2 tc = mix(tc1, tc2, gl_TessCoord.y);

	//interpolate the position and add the height value
	vec4 p1 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x);
	vec4 p2 = mix(gl_in[2].gl_Position, gl_in[3].gl_Position, gl_TessCoord.x);
	vec4 pos = mix(p1, p2, gl_TessCoord.y);
	pos.y += texture(heightMapSampler, tc).r * height;

	tesOut.heightTc = tc;
	tesOut.worldCoord = pos.xyz;

	vec4 eyeCoord = mvMatrix * pos;
	tesOut.eyeCoord = eyeCoord.xyz;
	gl_Position =  projMatrix * eyeCoord;
}