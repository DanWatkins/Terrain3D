//==================================================================================================================|
// Created 2015.03.17 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Tests.h"
#include <World/Terrain/Renderer.h>

using namespace t3d::world::terrain;
#define CLASS Test_WorldTerrainRenderer

TEST_CLASS
{
protected:
};



TEST_CASE(ConnectedToDataSignals)
{
	class MyRenderer : public Renderer
	{
	protected:
		void updateUniformValues()
		{
			++hitCount;
		}

	public:
		int hitCount = 0;
	};
}
