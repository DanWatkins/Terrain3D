#version 420 core

layout (location = 0) in int vertIndex;

layout (binding = 2) uniform samplerBuffer daBuf;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;

void main()
{
	int search = vertIndex * 3;

	vec4 pos;
	pos.x = texelFetch(daBuf, search+0).r;
	pos.y = texelFetch(daBuf, search+1).r;
	pos.z = texelFetch(daBuf, search+2).r;
	pos.w = 1.0f;

	float scale = 1.5f;
	gl_Position = cameraMatrix * modelMatrix * vec4(pos.x*scale, pos.y*scale, pos.z*scale, pos.w);
}
