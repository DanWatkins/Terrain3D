//==================================================================================================================|
// Created 2015.01.21 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Manager.h"

namespace t3d { namespace asset
{
	void Manager::loadMeshesFromDirectory(const QString path)
	{
		qDebug() << "Loading meshes...";
		loadSystemMeshes(path + "/_system/");

		QDirIterator iter(path);
		while (iter.hasNext())
		{
			QFileInfo info(iter.next());
			
			//skip the system dir
			if (info.dir().dirName() == "_system")
				continue;

			loadMesh(info.absoluteFilePath());
		}
	}


	void Manager::loadSystemMeshes(const QString &path)
	{
		QDirIterator iter(path);
		while (iter.hasNext())
		{
			loadMesh(iter.next());
		}
	}


	void Manager::loadMesh(const QString &path)
	{
		QFileInfo info(path);

		if (info.isFile())
		{
			if (info.suffix() == "t3m")
			{
				strong<Mesh> mesh(new Mesh);
				if (mesh->init(this, info.filePath()))
				{
					MeshQueue mq;
					mq.mesh = mesh;
					mMeshQueues.append(mq);
				}
			}
		}
	}


	strong<Mesh> Manager::meshForName(const QString name) const
	{
		for (const MeshQueue &mq : mMeshQueues)
		{
			if (mq.mesh->name() == name)
				return mq.mesh;
		}

		return nullptr;
	}
}}