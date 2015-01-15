//==================================================================================================================|
// Created 2015.01.13 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_World_Entity_RenderComponent_H
#define _t3d_World_Entity_RenderComponent_H

#include "BaseEntity.h"
#include <Core/Mesh/OBJ.h>

namespace t3d { namespace World { namespace Entity
{
	class BaseEntity::RenderComponent
	{
	public:
		void loadMesh(const QString &filepath);
		void render(const Mat4 &cameraMatrix);

	private:
		OBJ mMesh;
	};
}}}

#endif

