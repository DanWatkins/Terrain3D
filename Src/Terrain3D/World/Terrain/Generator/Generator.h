//==================================================================================================================|
// Created 2014.05.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _WORLD_TERRAIN_GENERATOR_H
#define _WORLD_TERRAIN_GENERATOR_H

#include <Terrain3D/Library.h>
#include <Terrain3D/World/Terrain/Data.h>

namespace t3d::world::terrain::Generator
{

class Generator
{
public:
    virtual void generate(Data &terrainData, int size, int numberOfPasses, float smoothing,
                          int seed) = 0;
};

}

#endif
