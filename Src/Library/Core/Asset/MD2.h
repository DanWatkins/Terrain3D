//==================================================================================================================|
// Created 2014.11.18 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_CORE_MD2_H
#define _t3d_CORE_MD2_H

#include <Library.h>
#include <Core/Image.h>
#include <Core/OpenGLFunctions.h>

namespace t3d { namespace Asset
{
	class MD2 : protected OpenGLFunctions
	{
	public:
		void setSkin(int skin);
		void setSkin(Image &image);
		bool load(const QString &filepath);

		void render();
		void render(int frame);
		void animate(float speed=30.0f, int startFrame=0, int endFrame=0, bool loop=true);

		MD2();
		MD2(const QString &filepath);
		~MD2();

	private:
		struct Header
		{
			int magicNum; //Always IDP2 (844121161)
			int version;  //8
			int skinWidthPx;
			int skinHeightPx;
			int frameSize;
			int numSkins;
			int numVertices;
			int numTexCoords;
			int numTriangles;
			int numGLCommands;
			int numFrames;
			int offsetSkins;
			int offsetTexCoords;
			int offsetTriangles;
			int offsetFrames;
			int offsetGlCommands;
			int fileSize;
		};

		Header mHeader;
		int mSkin;
		bool mIsCustomSkin;
		Image *mImage;


		struct Vertex
		{
			float values[3];
			unsigned char reserved;
		};


		struct Frame
		{
			float scale[3];
			float translation[3];
			char name[16];
			Vertex *vertecies;

			Frame()
			{
				vertecies = nullptr;
			}

			~Frame()
			{
				if (vertecies)
					delete [] vertecies;
			}
		};


		struct Triangle
		{
			unsigned short vertexIndicies[3];
			unsigned short textureIndicies[3];
		};


		struct TextureCoordinate
		{
			float pos[2];
		};


		struct Skin
		{
			char skin[64];
			Image image;
		};
	};
}}

#endif

