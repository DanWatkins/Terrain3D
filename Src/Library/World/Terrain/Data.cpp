//==================================================================================================================|
// Created 2014.11.02 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <World/Terrain/Data.h>

namespace t3d { namespace World { namespace Terrain
{
	int indexForHeight(const Data::HeightIndex &hi, float height)
    {
		Data::HeightIndex::ConstIterator iter = hi.cbegin();
		while (iter != hi.cend())
		{
			if (height <= iter.key())
				return iter.value();

			++iter;
		}

		return hi.first();
    }


	void Data::computeTextureIndicies(const HeightIndex &heightIndex)
    {
        int tcRes = mTextureMapResolution;
		int hmSize = mHeightMap.size();
        int tcmSize = (hmSize-1)*tcRes + 1;
        mTextureIndicies.resize(tcmSize*tcmSize);

        for (int y=0; y<tcmSize; ++y)
        {
            for (int x=0; x<tcmSize; ++x)
            {
                if (x%tcRes==0 && y%tcRes==0)
                {
					float height = mHeightMap.get(x/tcRes + y/tcRes*hmSize);
					mTextureIndicies[x + y*tcmSize] = indexForHeight(heightIndex, height);
                }
                else
                {
                    int pX = x/tcRes;
                    int nX = std::min(pX+1, hmSize-1);
                    int pY = y/tcRes;
                    int nY = std::min(pY+1, hmSize-1);

					float a = mHeightMap.get(pX, pY);
					float b = mHeightMap.get(nX, pY);
					float c = mHeightMap.get(pX, nY);
					float d = mHeightMap.get(nX, nY);

                    int rX = x % tcRes;
					int rY = y % tcRes;

					float dX = rX / float(tcRes);
					float dY = rY / float(tcRes);

                    //lerp
                    float h1 = a*(1.0f-dX) + b*dX;
                    float h2 = c*(1.0f-dX) + d*dX;
                    float height = h1*(1.0f-dY) + h2*dY;
					mTextureIndicies[x + y*tcmSize] = indexForHeight(heightIndex, height);
                }
            }
        }
    }
}}}
