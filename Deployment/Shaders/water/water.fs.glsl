#version 410 core

//==================================================================================================================|
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

out vec4 outColor;

in vec2 tc;

uniform sampler2D waterTexture;

void main()
{
	outColor = vec4(texture(waterTexture, tc).xyz, 0.75);
}