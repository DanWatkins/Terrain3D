#ifndef _t3d_UTILITY_H
#define _t3d_UTILITY_H

#include <Main.h>

namespace t3d
{
	int maxLevelsOfDetail(int blockSize);
	int sizeForLod(int lod);
	double blockDistanceBetweenPos(Vec2i a, Vec2i b);
	int lodForDistance(double distance);
}

#endif
