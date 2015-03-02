//==================================================================================================================|
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#version 420 core

layout (quads, fractional_odd_spacing) in;

in TCSOut
{
	vec2 tc;
} tesIn[];


out TESOut
{
	vec2 tc;
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
	vec2 tc1 = mix(tesIn[0].tc, tesIn[1].tc, gl_TessCoord.x);
	vec2 tc2 = mix(tesIn[2].tc, tesIn[3].tc, gl_TessCoord.x);
	vec2 tc = mix(tc2, tc1, gl_TessCoord.y);

	//interpolate the position and add the height value
	vec4 p1 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x);
	vec4 p2 = mix(gl_in[2].gl_Position, gl_in[3].gl_Position, gl_TessCoord.x);
	vec4 pos = mix(p2, p1, gl_TessCoord.y);
	pos.y += texture(heightMapSampler, tc).r * height;

	tesOut.tc = tc;
	tesOut.worldCoord = pos.xyz;

	vec4 eyeCoord = mvMatrix * pos;
	tesOut.eyeCoord = eyeCoord.xyz;
	gl_Position =  projMatrix * eyeCoord;
}