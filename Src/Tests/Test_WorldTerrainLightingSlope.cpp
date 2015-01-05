#include "Main.h"
#include <World/Terrain/Lighting/Slope.h>
#include <World/Terrain/LightMap.h>
#include <World/Terrain/HeightMap.h>

using namespace t3d::World::Terrain;

#define CLASS Test_WorldTerrainLightingSlope

TEST_CLASS
{
protected:
};

TEST_CASE(passThrough)
{
	const int size = 8;

	HeightMap hm;
	hm.reserve(size);

	for (int y=0; y<size; y++)
	{
		for (int x=0; x<size; x++)
			hm.set(x, y, 0.0f);
	}

	LightMap lm;
	lm.reserve(size);

	Lighting::Slope::computeBrightness(lm, hm, 12.0f);

	//since all heights are the same, the sun can shine everywhere!
	const float maxBrightness = 1.0f;

	for (int y=0; y<size; y++)
	{
		for (int x=0; x<size; x++)
			EXPECT_EQ(maxBrightness, lm.get(x, y));
	}
}


TEST_CASE(differentSizes)
{
	HeightMap hm;
	hm.reserve(8);

	LightMap lm;
	lm.reserve(16);

	//should return false since the sizes are different
	ASSERT_FALSE(Lighting::Slope::computeBrightness(lm, hm, 12.0f));
}
