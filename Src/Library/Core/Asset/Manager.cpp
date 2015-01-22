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
					strong<priv::OBJ> obj(new priv::OBJ);
					if (obj->initWithFile(info.filePath()))
						mMeshList.append(obj);
				}
			}
		}
	}


	strong<priv::OBJ> Manager::meshForName(const QString name) const
	{
		QListIterator<strong<priv::OBJ>> iter(mMeshList);
		iter.toFront();

		while (iter.hasNext())
		{
			strong<priv::OBJ> current = iter.next();
			if (current->name() == name)
				return current;
		}

		return nullptr;
	}
}}