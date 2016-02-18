//==================================================================================================================|
// Created 2014.11.19 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_CORE_OBJ_H
#define _t3d_CORE_OBJ_H

#include <Terrain3D/Library.h>
#include "MeshPrivate.h"

namespace t3d { namespace asset {

class OBJ
{
public:
	bool initWithFile(const QString &filepath, mesh_p *mesh);

private:
	mesh_p *mCurrentMesh;

	bool parseFile(const QString &filepath);
	bool parseField(const QStringList &field);
	bool parseMaterialLib(const QString &filepath);
	bool parseMaterialLibField(const QStringList &field);
};

}}

#endif

