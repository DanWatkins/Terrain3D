//==================================================================================================================|
// Created 2014.10.31 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_UTILITY_H
#define _t3d_UTILITY_H

#include <Terrain3D/Library.h>

namespace t3d::world::terrain
{

int maxLevelsOfDetail(int blockSize);
int sizeForLod(int lod);
double lodDistanceBetweenPos(Vec2i a, Vec2i b, int blockSize);
int lodForDistance(double distance, int blockSize, float factor);

}

#endif
