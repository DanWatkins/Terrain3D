#version 420 core

layout (location = 0) in vec4 position;
layout (location = 1) in int brightness;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;
uniform float heightScale = 10.0f;
uniform float spacing;
uniform float blockSize;
uniform ivec2 blockIndex;
uniform float spanSize;

smooth out vec2 tc;
smooth out vec4 outPos;
smooth out float vsBrightness;

void main()
{
	float repeatFactor = blockSize / spanSize;

	tc.x = repeatFactor * (position.x/spacing - float(blockIndex.x)*blockSize) / blockSize;
	tc.y = repeatFactor * (position.z/spacing - float(blockIndex.y)*blockSize) / blockSize;

	outPos = position;

	vsBrightness = float(brightness) / 65535.0f;

	vec4 scaledPosition = vec4(position.x, position.y*heightScale, position.z, position.w);
	gl_Position = cameraMatrix * modelMatrix * scaledPosition;
}
