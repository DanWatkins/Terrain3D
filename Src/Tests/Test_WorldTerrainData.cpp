#include <gtest/gtest.h>
#include <World/Terrain/Data.h>

using namespace t3d::World::Terrain;

class Test_WorldTerrainData : public ::testing::Test
{
protected:
	void testComputeTextureIndiciesBasic(int size, float baseHeight, int expectedIndex, Data::HeightIndex &heightIndex)
	{
		Data data(1);
		data.heightMap().reserve(size);

		for (int y=0; y<size; y++)
		{
			for (int x=0; x<size; x++)
				data.heightMap().set(x, y, baseHeight);
		}

		data.computeTextureIndicies(heightIndex);

		std::vector<GLubyte> ti = data.textureIndicies();
		for (unsigned i=0; i<ti.size(); i++)
			ASSERT_EQ(expectedIndex, ti[i]);
	}
};


TEST_F(Test_WorldTerrainData, computeTextureIndicies1)
{
	Data::HeightIndex hi;
	hi[0.5f] = 0;
	hi[0.7f] = 1;

	testComputeTextureIndiciesBasic(2, 0.0f, 0, hi);
}


TEST_F(Test_WorldTerrainData, computeTextureIndicies2)
{
	Data::HeightIndex hi;
	hi[0.1f] = 0;
	hi[0.7f] = 4;
	hi[1.0f] = 7;

	testComputeTextureIndiciesBasic(5, 140.0f, 4, hi);
}
