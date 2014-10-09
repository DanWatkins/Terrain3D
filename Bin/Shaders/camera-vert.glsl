#version 330 core

layout (location = 0) in vec4 position;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;
uniform float heightScale = 10.0f;
uniform float spacing;
uniform float blockSize;

smooth out vec2 tc;
smooth out vec4 outPosition;


void main()
{
	tc.x = (position.x / spacing / blockSize);
	tc.y = (position.z / spacing / blockSize);

	vec4 scaledPosition = vec4(position.x, position.y*heightScale, position.z, position.w);

	outPosition = position;
	gl_Position = cameraMatrix * modelMatrix * scaledPosition;
}