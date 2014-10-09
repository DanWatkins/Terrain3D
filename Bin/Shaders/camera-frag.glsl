#version 330 core

smooth in vec2 tc;
smooth in vec4 outPosition;
out vec4 color;

uniform sampler2DArray sampler;
uniform float spacing;

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
	ivec3 txSize = textureSize(sampler, 0);
	ivec3 pos;
	
	pos.x = int(tc.x * txSize);
	pos.y = int(tc.y * txSize);
	pos.z = terrainLayer(outPosition.y);
	
	color = texelFetch(sampler, pos, 0);
}