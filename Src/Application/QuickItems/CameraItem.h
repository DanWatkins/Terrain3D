//==================================================================================================================|
// Created 2014.12.05 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_QUICK_ITEMS_CAMERA_H
#define _t3d_QUICK_ITEMS_CAMERA_H

#include <Core/OpenGLQuickItem.h>
#include <World/Camera.h>

namespace t3d { namespace QuickItems
{
	class CameraItem : public OpenGLQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(bool isLoaded READ isLoaded NOTIFY isLoadedChanged)

	private:
		typedef t3d::World::Camera ActualCamera;

	public:
		CameraItem();

		void setWorld(t3d::World::World *world);
		QWeakPointer<ActualCamera> camera() { return mCamera; }
		bool isLoaded() const { return mIsLoaded; }

		void init() override;
		void render() override;

		QSharedPointer<ActualCamera> mCamera;

	signals:
		void isLoadedChanged();

	private:
		void setIsLoaded(bool isLoaded);
		bool mIsLoaded;
	};
}}

#endif


