#version 420 core

//==================================================================================================================|
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

layout (vertices = 4) out;

in VSOut
{
	vec2 tc;
	int instanceId;
} tcsIn[];

out TCSOut
{
	vec2 tc;
} tcsOut[];

uniform int terrainSize;
uniform int chunkSize;
uniform float lod;
uniform float ivd; //everything within this distance should be full detail
uniform vec3 cameraPos;

const float minLevel = 1.0;
const float maxLevel = 100.0;

int lodForChunkPos(ivec2 chunkPos)
{
	vec3 realPos;
	realPos.x = float(chunkPos.x) * chunkSize + (chunkSize/2.0);
	realPos.y = 4.0;
	realPos.z = float(chunkPos.y) * chunkSize + (chunkSize/2.0);

	float invDistance = (terrainSize-distance(cameraPos, realPos) + ivd) / float(terrainSize);
	return int(max(invDistance * maxLevel * lod, minLevel));
}


void main()
{
	if (gl_InvocationID == 0)
	{
		const int chunksPerSide = terrainSize / chunkSize;
		ivec2 chunkPos;
		chunkPos.x = tcsIn[0].instanceId % chunksPerSide;
		chunkPos.y = tcsIn[0].instanceId / chunksPerSide;

		int inner = lodForChunkPos(chunkPos);

		gl_TessLevelOuter[0] = inner;
		gl_TessLevelOuter[1] = inner;
		gl_TessLevelInner[0] = inner;
		gl_TessLevelInner[1] = inner;

		//succumb to your neighbor to avoid cracking
		gl_TessLevelOuter[2] = lodForChunkPos(chunkPos+ivec2(0,1));
		gl_TessLevelOuter[3] = lodForChunkPos(chunkPos+ivec2(1,0));
	}
	
	
	tcsOut[gl_InvocationID].tc = tcsIn[gl_InvocationID].tc;
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}