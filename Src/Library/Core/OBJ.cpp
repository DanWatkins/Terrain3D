//==================================================================================================================|
// Created 2014.11.19 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "OBJ.h"

namespace t3d
{
	bool OBJ::load(const QString &filepath)
	{
		QFile file(filepath);

		if (!file.open(QIODevice::ReadOnly))
			return false;

		QTextStream ts(&file);
		int lineNumber = 0;

		while (!ts.atEnd())
		{
			QString line = ts.readLine();
			QStringList field = line.split(" ");

			if (!parseField(field))
			{
				qDebug() << filepath << "- Error parsing line " << lineNumber << ": " << line;
			}

			++lineNumber;
		}

		return true;
	}


	bool OBJ::parseField(const QStringList &field)
	{
		bool error = false;

		//4 component fields
		if (field.size() == 4)
		{
			//vertex
			if (field.front() == "v")
			{
			}
			else
				error = true;
		}
		//5 component fields
		else if (field.size() == 5)
		{
			//face
			if (field.front() == "f")
			{
			}
			else
				error = true;
		}
		//comment
		else if (field.at(0).startsWith("#"))
		{
			//do nothing
		}
		//blank line
		else if (field.size() == 0)
		{
			//do nothing
		}
		else
			error = true;

		return !error;
	}
}
