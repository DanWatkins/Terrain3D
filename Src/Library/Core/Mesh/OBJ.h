//==================================================================================================================|
// Created 2014.11.19 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_CORE_OBJ_H
#define _t3d_CORE_OBJ_H

#include <Library.h>

namespace t3d
{
	/**
	 * Wavefront OBJ mesh loader and renderer.
	 */
	class OBJ
	{
	public:
		OBJ();
		~OBJ();

		/**
		 * Loads an OBJ mesh file into memory and prepares for rendering.
		 */
		bool initWithFile(const QString &filepath);

		/**
		 * 
		 */
		void render(const Mat4 &totalMatrix);

	private:
		class OBJPrivate;
		unique<OBJPrivate> mPrivate;
	};
}

#endif

