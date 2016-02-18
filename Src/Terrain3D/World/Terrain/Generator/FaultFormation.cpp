#include "FaultFormation.h"

namespace t3d { namespace world { namespace terrain { namespace Generator {

void applyRandomFault(HeightMap &heightMap, float faultAmount)
{
	//create the fault line from two random points
	Vec2f p1((float)vbase::randInt(0, heightMap.size()), (float)vbase::randInt(0, heightMap.size()));
	Vec2f p2;

	do
	{
		p2 = Vec2f((float)vbase::randInt(0, heightMap.size()), (float)vbase::randInt(0, heightMap.size()));
	} while (p2 == p1);


	float dirX1 = p2.x-p1.x;
	float dirY1 = p2.y - p1.y;
	int size = heightMap.size();

	for (int y=0; y<size; y++)
	{
		for (int x=0; x<size; x++)
		{
			float dirX2 = x - p1.x;
			float dirY2 = y - p1.y;

			if ((dirX2*dirY1 - dirX1*dirY2) > 0)
				heightMap.set(x, y, heightMap.get((GLuint)x, (GLuint)y) + faultAmount);
		}
	}
}


void normalizeHeights(HeightMap &heightMap)
{
	float min = heightMap.get(0);
	float max = heightMap.get(0);
	int size = heightMap.size();

	for (int i=1; i<size*size; i++)
	{
		if (heightMap.get(i) > max)
			max = heightMap.get(i);
		else if (heightMap.get(i) < min)
			min = heightMap.get(i);
	}


	if (max <= min)
		return;

	float height = max-min;

	for (int i=0; i<size*size; i++)
	{
		heightMap.set(i, (heightMap.get(i)-min) / height);
	}
}


void smoothHeightBand(HeightMap &heightMap, GLuint index, int stride, GLuint length, float intensity)
{
	float v = heightMap.get(index);
	int j = stride;

	for (GLuint i=0; i<length-1; i++)
	{
		float height = (float)heightMap.get(j+index);
		heightMap.set(j+index, intensity*v + (1-intensity) * height);

		v = (float)heightMap.get(j + index);
		j += stride;
	}
}


void smoothHeight(HeightMap &heightMap, float intensity)
{
	int size = heightMap.size();

	//left to right
	for (int i = 0; i<size; i++)
		smoothHeightBand(heightMap, size*i, 1, size, intensity);

	//right to left
	for (int i = 0; i<size; i++)
		smoothHeightBand(heightMap, size*i + size-1, -1, size, intensity);

	//top to bottom
	for (int i = 0; i<size; i++)
		smoothHeightBand(heightMap, i, size, size, intensity);

	//bottom to top
	for (int i = 0; i<size; i++)
		smoothHeightBand(heightMap, size*(size-1)+i, -size, size, intensity);
}


void FaultFormation::generate(Data &terrainData, int size, int numberOfPasses, float smoothing, int seed)
{
	HeightMap heightMap;
	heightMap.reserve(size);
	std::srand(seed);

	for (int i=0; i<numberOfPasses; i++)
	{
		const float maxDelta = 255.0f;
		const float minDelta = 0.0f;
		float amount = maxDelta - ((maxDelta - minDelta) * i) / size;
		amount += 15.0f;

		applyRandomFault(heightMap, amount);
	}
	qDebug() << "      Built height map";

	smoothHeight(heightMap, smoothing);
	qDebug() << "      Smothed height map";

	normalizeHeights(heightMap);
	qDebug() << "      Normalized height map";

	terrainData.resetHeightMap(heightMap);
	qDebug() << "      Reseated the height map";
}

}}}}
