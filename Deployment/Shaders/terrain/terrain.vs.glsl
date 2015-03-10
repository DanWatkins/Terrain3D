#version 420 core

//==================================================================================================================|
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

uniform int terrainSize;
uniform int chunkSize;

out VSOut
{
	vec2 tc;
	int instanceId;
} vsOut;


void main()
{
	const vec3 vertices[] = vec3[](vec3(1.0, 0.0, 0.0),
                                   vec3(1.0, 0.0, 1.0),
                                   vec3(0.0, 0.0, 0.0),
                                   vec3(0.0, 0.0, 1.0));
	
	
	const int chunksPerSide = terrainSize / chunkSize;

	vec2 offset;
	offset.x = (gl_InstanceID % chunksPerSide) * chunkSize;
	offset.y = (gl_InstanceID / chunksPerSide) * chunkSize;

	vec2 pos = vertices[gl_VertexID].xz * chunkSize + offset;

	vsOut.tc = pos / vec2(terrainSize, terrainSize);
	vsOut.instanceId = gl_InstanceID;

	gl_Position = vec4(pos.x, 0.0, pos.y, 1.0);
}