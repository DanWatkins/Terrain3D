#include "Utility.h"

namespace t3d
{
	int maxLevelsOfDetail(int blockSize)
	{
		return int(std::log10(blockSize)/std::log10(2) + 0.5);
	}


	int sizeForLod(int lod)
	{
		return std::pow(2, lod+1);
	}


	double blockDistanceBetweenPos(Vec2i a, Vec2i b)
	{
		Vec2i net(a.x-b.x, a.y-b.y);

		return std::sqrt(net.x*net.x + net.y*net.y);
	}


	int lodForDistance(double distance)
	{
		return 0;
	}
}
