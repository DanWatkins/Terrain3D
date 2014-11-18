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

		QVector<GLubyte> ti = data.textureIndicies();
		for (int i=0; i<ti.size(); i++)
			ASSERT_EQ(expectedIndex, ti[i]);
	}


	void testComputeTextureIndiciesAdv(int size, int res, const Data::HeightIndex &hi, float *heights, GLubyte *expected)
	{
		Data data(res);
		data.heightMap().reserve(size);

		for (int y=0; y<size; y++)
		{
			for (int x=0; x<size; x++)
			{
				data.heightMap().set(x, y, heights[x + y*size]);
			}
		}

		data.computeTextureIndicies(hi);

		//verify
		for (int i=0; i<data.textureIndicies().size(); i++)
		{
			EXPECT_EQ(expected[i], data.textureIndicies()[i]) << "Index is " << i;
		}
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

	testComputeTextureIndiciesBasic(5, 0.53f, 4, hi);
}


TEST_F(Test_WorldTerrainData, computeTextureIndicies3)
{
	float heights[] =
	{
		0.490f, 0.740f,
		0.240f, 1.000f
	};

	GLubyte expected[] =
	{
		1, 2, 2,
		1, 2, 3,
		0, 2, 3
	};

	Data::HeightIndex hi;
	hi[0.25f] = 0;
	hi[0.50f] = 1;
	hi[0.75f] = 2;
	hi[1.00f] = 3;

	testComputeTextureIndiciesAdv(2, 2, hi, heights, expected);
}


TEST_F(Test_WorldTerrainData, computeTextureIndicies4)
{
	float heights[] =
	{
		0.00f, 0.49f, 0.74f,
		0.49f, 0.74f, 0.99f,
		0.74f, 0.99f, 0.74f,
	};

	GLubyte expected[] =
	{
		0, 0, 1, 2, 2,
		0, 1, 2, 2, 3,
		1, 2, 2, 3, 3,
		2, 2, 3, 3, 3,
		2, 3, 3, 3, 2
	};

	Data::HeightIndex hi;
	hi[0.25f] = 0;
	hi[0.50f] = 1;
	hi[0.75f] = 2;
	hi[1.00f] = 3;

	testComputeTextureIndiciesAdv(3, 2, hi, heights, expected);
}
