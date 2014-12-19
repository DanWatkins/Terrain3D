//==================================================================================================================|
// Created 2014.12.05 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_QUICK_ITEMS_CAMERA_H
#define _t3d_QUICK_ITEMS_CAMERA_H

#include <QtQuick/QQuickFramebufferObject>
#include <World/Camera.h>

namespace t3d
{
	extern World::Camera *theCamera;
}

namespace t3d { namespace QuickItems
{
	class CameraItem : public QQuickFramebufferObject
	{
		Q_OBJECT
		Q_PROPERTY(bool isLoaded READ isLoaded NOTIFY isLoadedChanged)

	public:
		Renderer *createRenderer() const;
		bool isLoaded() const { return theCamera != nullptr; }

	signals:
		void isLoadedChanged();
	};
}}

#endif


