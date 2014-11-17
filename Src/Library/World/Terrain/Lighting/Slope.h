//==================================================================================================================|
// Created 2014.11.02 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <World/Terrain/Data.h>

namespace t3d { namespace World { namespace Terrain {

	class HeightMap;
	class LightMap;

	namespace Lighting
	{
		class Slope
		{
		public:
			static bool computeBrightness(LightMap &lm, const HeightMap &hm);


		private:


		};
	}
}}}
