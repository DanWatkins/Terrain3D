#version 420 core

layout (location = 0) in int vertIndex;

layout (binding = 2) uniform samplerBuffer vertexPositions;
layout (binding = 3) uniform samplerBuffer vertexNormals;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;
uniform int indexCount;

out vec3 vertexNormal;

void main()
{
	//handle the vertex position
	{
		int search = vertIndex * 3;

		vec4 pos;
		pos.x = texelFetch(vertexPositions, search+0).r;
		pos.y = texelFetch(vertexPositions, search+1).r;
		pos.z = texelFetch(vertexPositions, search+2).r;
		pos.w = 1.0f;

		float scale = 1.5f;
		gl_Position = cameraMatrix * modelMatrix * vec4(pos.x*scale, pos.y*scale, pos.z*scale, pos.w);
	}

	//handle the vertex normal
	{
		int search = vertIndex*3;

		vertexNormal.x = texelFetch(vertexNormals, search+0).r;
		vertexNormal.y = texelFetch(vertexNormals, search+1).r;
		vertexNormal.z = texelFetch(vertexNormals, search+2).r;

		int dick = int(vertexNormal.z);
	}
}
