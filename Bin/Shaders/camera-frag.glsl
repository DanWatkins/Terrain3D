#version 430 core

smooth in vec2 tc;
smooth in vec4 outPosition;
out vec4 color;

uniform sampler2DArray sampler;
uniform float spacing;

//terrain layers
const int TerrainLayer_Water = 0;
const int TerrainLayer_Sand = 1;
const int TerrainLayer_Grass = 2;
const int TerrainLayer_Mountain = 3;

int terrainLayer(float height)
{
	if (height > 0.8f)
		return TerrainLayer_Mountain;
	else if (height > 0.6f)
		return TerrainLayer_Grass;
	else if (height > 0.35f)
		return TerrainLayer_Sand;
	else if (height > 0.0f)
		return TerrainLayer_Water;
}


void main()
{
	vec3 pos;
	pos.x = tc.x;
	pos.y = tc.y;
	pos.z = terrainLayer(outPosition.y);

	color = texture(sampler, pos);
}