//==================================================================================================================|
// Created 2015.01.13 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_MANAGER_H
#define _t3d_MANAGER_H

#include <Library.h>

#include <World/Entity/BaseEntity.h>

namespace t3d { namespace World { namespace Entity
{
	class Manager : public QObject
	{
		Q_OBJECT

	public:
		Manager();

		strong<BaseEntity> createEntity();
		strong<BaseEntity> findEntity(int id);

		const QVector<strong<BaseEntity>> &entityContainer() const { return mEntityContainer; }

	private:
		QVector<strong<BaseEntity>> mEntityContainer;	//TODO finish ReuseVector and use it here!
		int mIdValueTrack;
	};
}}}

#endif

