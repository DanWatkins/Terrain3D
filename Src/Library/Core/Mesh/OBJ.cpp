//==================================================================================================================|
// Created 2014.11.19 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "OBJ.h"

#include "./private/MaterialData.h"
#include "./private/FaceData.h"
#include "./private/SubMesh.h"

namespace t3d
{
	void removeLastPathComponent(QString &filepath)
	{
		filepath = "../Meshes/"; //TODO massive temporary hack
	}


	bool OBJ::initWithFile(const QString &filepath)
	{
		OpenGLFunctions::initializeOpenGLFunctions();
		
		mContainingDirectory = mFilepath = filepath;
		removeLastPathComponent(mContainingDirectory);
		
		if (parseFile(filepath))
		{
			init();
			return true;
		}

		return false;
	}


	///// PRIVATE

	bool OBJ::parseFile(const QString &filepath)
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
		//material lib
		if (field.front() == "mtllib" && field.count() == 2)
		{
			parseMaterialLib(mContainingDirectory + "/" + field.at(1));
		}
		//use material - aka create a new SubMesh
		else if (field.front() == "usemtl" && field.count() == 2)
		{
			mSubMesh.append(strong<SubMesh>(new SubMesh));
			mSubMesh.last()->mMaterial = field.at(1);
		}

		//vertex
		else if (field.front() == "v" && field.count() == 4)
		{
			Vertex vertex;
			vertex.values[0] = field.at(1).toFloat();
			vertex.values[1] = field.at(2).toFloat();
			vertex.values[2] = field.at(3).toFloat();
			mFaceData->mVertecies.push_back(vertex);
		}
		//vertex normal
		else if (field.front() == "vn" && field.count() == 4)
		{
			Vertex vertex;
			vertex.values[0] = field.at(1).toFloat();
			vertex.values[1] = field.at(2).toFloat();
			vertex.values[2] = field.at(3).toFloat();
			mFaceData->mVertexNormals.push_back(vertex);
		}
		//vertex texture coordinate
		else if (field.front() == "vt" && (field.count() == 3 || field.count() == 4))
		{
			Vertex vertex;
			vertex.values[0] = field.at(1).toFloat();
			vertex.values[1] = field.at(2).toFloat();
			if (field.count() == 4)
				vertex.values[2] = field.at(3).toFloat();
			mFaceData->mTextureCoordinates.push_back(vertex);
		}
		//face
		else if (field.front() == "f"  &&  field.size() >= 4)
		{
			Face face;

			for (int i=0; i<field.size()-1; i++)
			{
				QStringList cmp = field.at(i+1).split("/");

				if (cmp.size() > 0)
					face.vertexIndex.push_back(cmp.at(0).toInt()-1);
				if (cmp.size() > 1)
					face.textureIndex.push_back(cmp.at(1).toInt()-1);
				if (cmp.size() > 2)
					face.normalIndex.push_back(cmp.at(2).toInt()-1);
			}

			mSubMesh.last()->mFaces.push_back(face);
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
			qDebug() << "Blank line";
		}
		else
			return false;

		return true;
	}


	bool OBJ::parseMaterialLib(const QString &filepath)
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

			if (!parseMaterialLibField(field))
			{
				qDebug() << filepath << "- Error parsing line " << lineNumber << ": " << line;
			}

			++lineNumber;
		}

		return true;
	}


	bool OBJ::parseMaterialLibField(const QStringList &field)
	{
		//new material
		if (field.front() == "newmtl" && field.count() == 2)
		{
			mMaterials.append(strong<MaterialData>(new MaterialData));
			mMaterials.last()->mName = field.at(1);
		}
		//texture map - diffuse
		else if (field.front() == "map_Kd" && field.count() == 2)
		{
			mMaterials.last()->mFilepath = field.at(1);
		}
		else
		{
			//unknown
			return false;
		}

		return true;
	}
}
