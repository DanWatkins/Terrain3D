//==================================================================================================================|
// Created 2015.01.21 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_AssetManager_H
#define _t3d_AssetManager_H

#include <Library.h>
#include <Core/Asset/Mesh.h>

namespace t3d { namespace Asset
{
	class Manager
	{
	public:
		friend class Mesh;

		void loadMeshesFromDirectory(const QString path);
		int meshCount() const { return mMeshQueues.count(); }
		strong<Mesh> meshForName(const QString name) const;


		void renderAllQueued()
		{
			for (MeshQueue &mq : mMeshQueues)
			{
				for (Mat4 &m : mq.matricies)
					mq.mesh->render(m);
			}
		}

	private:
		struct MeshQueue
		{
			strong<Mesh> mesh;
			QVector<Mat4> matricies;
		};

		QList<MeshQueue> mMeshQueues;

		void queueMeshRender(Mesh *mesh, const Mat4 &totalMatrix)
		{
			for (MeshQueue &mq : mMeshQueues)
			{
				if (mq.mesh.get() == mesh)
				{
					mq.matricies.append(totalMatrix);
					break;
				}
			}
		}
	};
}}

#endif

