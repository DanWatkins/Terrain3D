#version 420 core

//==================================================================================================================|
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

uniform int terrainSize;
uniform int chunkSize;
uniform ivec2 chunkPos;

out VSOut
{
	vec2 tc;
} vsOut;


void main()
{
	const vec4 vertices[] = vec4[](vec4(1.0, 0.0, 0.0, 1.0),
                                   vec4(1.0, 0.0, 1.0, 1.0),
                                   vec4(0.0, 0.0, 0.0, 1.0),
                                   vec4(0.0, 0.0, 1.0, 1.0));
	
	
	vec2 pos;
	pos.x = gl_InstanceID % chunkSize + (chunkPos.x * chunkSize);
	pos.y = gl_InstanceID / chunkSize + (chunkPos.y * chunkSize);

	vsOut.tc = (vertices[gl_VertexID].xz + pos) / terrainSize;
	gl_Position = vertices[gl_VertexID] + vec4(pos.x, 0, pos.y, 0);	
}