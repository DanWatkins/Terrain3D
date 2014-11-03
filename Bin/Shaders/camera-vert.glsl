#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in int inTextureIndex;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;
uniform float heightScale = 10.0f;
uniform float spacing;
uniform float blockSize;
uniform ivec2 blockIndex;

smooth out vec2 tc;
flat out int outTextureIndex;

void main()
{
	tc.x = (position.x/spacing - float(blockIndex.x)*blockSize) / blockSize;
	tc.y = (position.z/spacing - float(blockIndex.y)*blockSize) / blockSize;
	vec4 scaledPosition = vec4(position.x, position.y*heightScale, position.z, position.w);

	outTextureIndex = 2;
	gl_Position = cameraMatrix * modelMatrix * scaledPosition;
}
