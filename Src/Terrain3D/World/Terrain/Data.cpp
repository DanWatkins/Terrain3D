//==================================================================================================================|
// Created 2014.11.02 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <World/Terrain/Data.h>

namespace t3d { namespace World { namespace Terrain
{
	Data::Data()
	{
		mTextureMapResolution = 2;
	}


    int indexForHeight(float height)
    {
        //which texture should we use?
        if (height > 0.8f) //mountain
            return 3;
        else if (height > 0.4f) //grass
            return 2;
        else if (height > 0.2f) //sand
            return 1;
        else                    //water
            return 0;
    }


	void Data::computeTextureIndicies()
    {
        int tcRes = mTextureMapResolution;
        int hmSize = mHeightMap.getSize();
        int tcmSize = (hmSize-1)*tcRes + 1;
        mTextureIndicies.resize(tcmSize*tcmSize);

        for (int y=0; y<tcmSize; ++y)
        {
            for (int x=0; x<tcmSize; ++x)
            {
                if (x%tcRes==0 && y%tcRes==0)
                {
                    float height = mHeightMap.get(x/tcRes + y/tcRes*hmSize) / 255.0f;
                    mTextureIndicies[x + y*tcmSize] = indexForHeight(height);
                }
                else
                {
                    int pX = x/tcRes;
                    int nX = std::min(pX+1, hmSize-1);
                    int pY = y/tcRes;
                    int nY = std::min(pY+1, hmSize-1);

                    float a = mHeightMap.get(pX, pY) / 255.0f;
                    float b = mHeightMap.get(nX, pY) / 255.0f;
                    float c = mHeightMap.get(pX, nY) / 255.0f;
                    float d = mHeightMap.get(nX, nY) / 255.0f;

                    int rX = x % tcRes;
                    int rY = y & tcRes;

                    float dX = rX / float(tcRes+1);
                    float dY = rY / float(tcRes+1);

                    //lerp
                    float h1 = a*(1.0f-dX) + b*dX;
                    float h2 = c*(1.0f-dX) + d*dX;
                    float height = h1*(1.0f-dY) + h2*dY;
                    mTextureIndicies[x + y*tcmSize] = indexForHeight(height);
                }
            }
        }
    }
}}}
