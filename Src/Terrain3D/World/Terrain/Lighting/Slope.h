//==================================================================================================================|
// Created 2014.11.02 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <Terrain3D/World/Terrain/Data.h>

namespace t3d::world::terrain {

class HeightMap;
class LightMap;

namespace Lighting {

class Slope
{
public:
    static bool computeBrightness(LightMap &lm, const HeightMap &hm, float intensity);
};

}}
