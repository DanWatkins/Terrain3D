#ifndef _TEST_WORLD_TERRAIN_DATA_H
#define _TEST_WORLD_TERRAIN_DATA_H

#include "AutoTest.h"

#include <World/Terrain/Data.h>

using namespace t3d::World::Terrain;

class Test_WorldTerrainData : public QObject
{
	Q_OBJECT

private slots:
	void computeTextureIndicies1()
	{
		Data::HeightIndex hi;
		hi[0.5f] = 0;
		hi[0.7f] = 1;

		testComputeTextureIndiciesBasic(2, 0.0f, 0, hi);
	}


	void computeTextureIndicies2()
	{
		Data::HeightIndex hi;
		hi[0.1f] = 0;
		hi[0.7f] = 4;
		hi[1.0f] = 7;

		testComputeTextureIndiciesBasic(5, 140.0f, 4, hi);
	}


private:
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
		for (int i=0; i<ti.size(); i++)
			QCOMPARE(static_cast<int>(ti[i]), expectedIndex);
	}
};

DECLARE_TEST(Test_WorldTerrainData)


#endif
