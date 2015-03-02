//==================================================================================================================|
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#version 420 core

in TESOut
{
	vec2 tc;
	vec3 worldCoord;
	vec3 eyeCoord;
} fsIn;

out vec4 color;

uniform float height;


void main()
{
	float scale = fsIn.worldCoord.y / height;
	color = vec4(scale, scale, scale, 1.0);
}