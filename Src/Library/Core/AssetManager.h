//==================================================================================================================|
// Created 2015.01.21 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_AssetManager_H
#define _t3d_AssetManager_H

#include "../Library.h"
#include <Core/Mesh/OBJ.h>

namespace t3d
{
	class AssetManager
	{
	public:
		void loadMeshesFromDirectory(const QString path);
		int meshCount() const { return mMeshList.count(); }
		strong<OBJ> meshForName(const QString name) const;

	private:
		QList<strong<OBJ>> mMeshList;
	};
};

#endif

