#version 420 core

//==================================================================================================================|
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

uniform mat4 mvMatrix;
uniform mat4 projMatrix;
uniform int size;
uniform int spanSize;
uniform float waterLevel;

out vec2 tc;

void main()
{
	const vec4 vertices[] = vec4[](vec4(1.0, 0.0, 0.0, 1.0),
                                   vec4(1.0, 0.0, 1.0, 1.0),
                                   vec4(0.0, 0.0, 0.0, 1.0),
                                   vec4(0.0, 0.0, 1.0, 1.0));
	
	
	vec4 pos = vertices[gl_VertexID];
	tc.x = pos.x * size / spanSize;
	tc.y = pos.z * size / spanSize;

	gl_Position = projMatrix * mvMatrix * vec4(pos.x*size, waterLevel, pos.z*size, 1);	
}