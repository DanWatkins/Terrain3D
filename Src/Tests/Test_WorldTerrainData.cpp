#include "Tests.h"
#include "Reciever.h"
#include <World/Terrain/Data.h>

using namespace t3d::world::terrain;

#define CLASS Test_WorldTerrainData

TEST_CLASS
{
protected:
	void testComputeTextureIndiciesBasic(int size, float baseHeight, int expectedIndex, Data::HeightIndex &heightIndex)
	{
		Data data;
		data.setTextureMapResolution(1);
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

	void testComputeTextureIndiciesAdv(int size, const Data::HeightIndex &hi, float *heights, GLubyte *expected)
	{
		Data data;
		data.setTextureMapResolution(2);
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

	template<typename T>
	void testPropertyChangeAndNotify(void(Data::*signalFunction)(), void(Data::*setFunction)(T), int expectedCount, std::initializer_list<T> testCalls)
	{
		Data data;
		int times = 0;

		QObject::connect(&data, signalFunction, [&]()
		{
			++times;
		});

		for (const T &what : testCalls)
			(data.*setFunction)(what);

		ASSERT_EQ(expectedCount, times);
	}
};


TEST_CASE(computeTextureIndicies1)
{
	Data::HeightIndex hi;
	hi[0.5f] = 0;
	hi[0.7f] = 1;

	testComputeTextureIndiciesBasic(2, 0.0f, 0, hi);
}


TEST_CASE(computeTextureIndicies2)
{
	Data::HeightIndex hi;
	hi[0.1f] = 0;
	hi[0.7f] = 4;
	hi[1.0f] = 7;

	testComputeTextureIndiciesBasic(5, 0.53f, 4, hi);
}


TEST_CASE(computeTextureIndicies3)
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

	testComputeTextureIndiciesAdv(2, hi, heights, expected);
}


TEST_CASE(computeTextureIndicies4)
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

	testComputeTextureIndiciesAdv(3, hi, heights, expected);
}


TEST_CASE(Property_TextureMapResolution)
{
	testPropertyChangeAndNotify<int>(&Data::textureMapResolutionChanged, &Data::setTextureMapResolution, 2, {40, 40, 50});
}

TEST_CASE(Property_HeightScaleChanged)
{
	testPropertyChangeAndNotify<float>(&Data::heightScaleChanged, &Data::setHeightScale, 2, {40, 40, 50});
}

TEST_CASE(Property_SpanSize)
{
	testPropertyChangeAndNotify<int>(&Data::spanSizeChanged, &Data::setSpanSize, 2, {40, 40, 50});
}

TEST_CASE(Property_ChunkSize)
{
	testPropertyChangeAndNotify<int>(&Data::chunkSizeChanged, &Data::setChunkSize, 2, {40, 40, 50});
}