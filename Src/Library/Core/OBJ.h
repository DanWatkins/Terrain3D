//==================================================================================================================|
// Created 2014.11.19 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_CORE_MD2_H
#define _t3d_CORE_MD2_H

#include <Main.h>
#include <Core/Image.h>
#include <Core/OpenGLFunctions.h>

namespace t3d
{
	class OBJ : protected OpenGLFunctions
	{
	public:
		bool load(const QString &filepath);
		void render();

	private:
		struct Vertex
		{
			float values[3];
		};

		struct Face
		{
			int indicies[4];
		};

		QVector<Vertex> mVertecies;
		QVector<Face> mFaces;

	private:
		bool parseField(const QStringList &field);
	};
}

#endif

