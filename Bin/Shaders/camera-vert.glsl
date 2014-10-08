#version 330 core

layout (location = 0) in vec4 position;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;
uniform float heightScale = 10.0f;
uniform float spacing;

out vec4 shaderColor;
out vec4 outPosition;

out vec2 tc;

//terrain layers
const int TerrainLayer_Water = 0;
const int TerrainLayer_Sand = 1;

int terrainLayer(float height)
{
	if (height > 0.5f)
		return TerrainLayer_Sand;
	else if (height > 0.0f)
		return TerrainLayer_Water;
}


vec4 terrainColor(int layer)
{
	switch (layer)
	{
	case TerrainLayer_Water:
		return vec4(0.0f, 0.0f, 0.6f, 1.0f);
	case TerrainLayer_Sand:
		return vec4(0.8f, 0.8f, 0.6f, 1.0f);
	}
}


void main()
{	
	tc.x = position.x / spacing / spacing;
	tc.y = position.z / spacing / spacing;

	shaderColor = terrainColor(terrainLayer(position.y));

	vec4 scaledPosition = vec4(position.x, position.y*heightScale, position.z, position.w);
	outPosition = scaledPosition;

	gl_Position = cameraMatrix * modelMatrix * scaledPosition;
}