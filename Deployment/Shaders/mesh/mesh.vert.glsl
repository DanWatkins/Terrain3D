#version 420 core

layout (location = 0) in int indexVertexPosition;
layout (location = 1) in int indexVertexNormal;
layout (location = 2) in int indexTextureCoordinate;

layout (binding = 2) uniform samplerBuffer vertexPositions;
layout (binding = 3) uniform samplerBuffer vertexNormals;
layout (binding = 4) uniform samplerBuffer texCoordinates;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;
uniform int indexCount;

out vec3 vertexNormal;
out vec2 tc;

void main()
{
	//handle the vertex position
	{
		int search = indexVertexPosition*3;

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
		int search = indexVertexNormal*3;

		vertexNormal.x = texelFetch(vertexNormals, search+0).r;
		vertexNormal.y = texelFetch(vertexNormals, search+1).r;
		vertexNormal.z = texelFetch(vertexNormals, search+2).r;
	}
	
	//handle the texture coordinate
	{
		int search = indexTextureCoordinate*3;
		
		tc.x = texelFetch(texCoordinates, search+0).r;
		tc.y = texelFetch(texCoordinates, search+1).r;
	}
}