//==================================================================================================================|
// Created 2015.01.21 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Manager.h"

namespace t3d { namespace Asset
{
	void Manager::loadMeshesFromDirectory(const QString path)
	{
		QDirIterator iter(path, QDirIterator::Subdirectories);
		while (iter.hasNext())
		{
			QFileInfo info(iter.next());

			if (info.isFile())
			{
				if (info.suffix() == "obj")
				{
					strong<Mesh> mesh(new Mesh);
					if (mesh->initWithFile(info.filePath()))
						mMeshList.append(mesh);
				}
			}
		}
	}


	strong<Mesh> Manager::meshForName(const QString name) const
	{
		QListIterator<strong<Mesh>> iter(mMeshList);
		iter.toFront();

		while (iter.hasNext())
		{
			strong<Mesh> current = iter.next();
			if (current->name() == name)
				return current;
		}

		return nullptr;
	}
}}