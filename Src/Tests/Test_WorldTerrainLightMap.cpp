#include <gtest/gtest.h>
#include <World/Terrain/LightMap.h>

using namespace t3d::World::Terrain;

class Test_WorldTerrainLightMap : public ::testing::Test
{
protected:
	void testSimpleAssign(int size, float value)
	{
		LightMap lm;
		lm.reserve(size);

		for (int y=0; y<size; y++)
		{
			for (int x=0; x<size; x++)
				lm.set(x, y, value);
		}

		for (int y=0; y<size; y++)
		{
			for (int x=0; x<size; x++)
				EXPECT_EQ(value, lm.get(x, y));
		}
	}
};

TEST_F(Test_WorldTerrainLightMap, simpleAssign)
{
	testSimpleAssign(8, 0.9f);
}


TEST_F(Test_WorldTerrainLightMap, simpleAssign2)
{
	testSimpleAssign(16, 0.02f);
}


TEST_F(Test_WorldTerrainLightMap, accessRaw)
{
	const int size = 8;

	LightMap lm;
	lm.reserve(size);

	for (int y=0; y<size; y++)
	{
		for (int x=0; x<size; x++)
			lm.set(x, y, x%3 + y%2);
	}

	QVector<float> *raw = lm.raw();
	for (int y=0; y<size; y++)
	{
		for (int x=0; x<size; x++)
		{
			EXPECT_EQ(x%3 + y%2, raw->at(x + y*size));
		}
	}
}
