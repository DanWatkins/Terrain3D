#version 420 core

uniform int terrainSize;

out VSOut
{
	vec2 heightTc;
} vsOut;


void main()
{
	const float M = 0.5f;
	const vec4 vertices[] = vec4[](vec4(-M, 0.0, -M, 1.0),
                                   vec4( M, 0.0, -M, 1.0),
                                   vec4(-M, 0.0,  M, 1.0),
                                   vec4( M, 0.0,  M, 1.0));
	
	
	vec2 pos;
	pos.x = gl_InstanceID & (terrainSize-1);
	pos.y = gl_InstanceID / terrainSize;

	vsOut.heightTc = (vertices[gl_VertexID].xz + pos + vec2(M)) / terrainSize;
	gl_Position = vertices[gl_VertexID] + vec4(pos.x - terrainSize/2, 0, pos.y - terrainSize/2, 0);	
}