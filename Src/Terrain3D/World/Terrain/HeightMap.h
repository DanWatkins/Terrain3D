//==================================================================================================================|
// Created 2014.04.28 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_HEIGHT_MAP_H
#define _t3d_HEIGHT_MAP_H

#include <Main.h>
#include <vector>

namespace t3d { namespace World { namespace Terrain
{
	class HeightMap
	{
	private:
		std::vector<float> mHeightData;
		GLuint mSize;

		std::vector<float> mVertexData;

	public:
		HeightMap()
		{
			mSize = 0;
		}


		void reserve(GLuint size);
		void set(GLuint index, float height);
		void set(GLuint indexX, GLuint indexY, float height);
		float get(GLuint index) const;
		float get(GLuint indexX, GLuint indexY) const;

		void buildVertexData(float spacing);
		const std::vector<float> *getVertexData() const { return &mVertexData; }

		GLuint getSize() const { return mSize; }
	};
}}}


#endif

