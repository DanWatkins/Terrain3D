//==================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <QtGui/QGuiApplication>

#include "Main.h"
#include "Terrain3D.h"

#include <QuickItems/CameraItem.h>

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	//set all the QuickItem types
	{
		using namespace t3d::QuickItems;

		qmlRegisterType<CameraItem>("Terrain3D", 1, 0, "Camera");
	}

	int execReturn = 0;
	{
		t3d::Terrain3D mainWindow;
		mainWindow.init();
		mainWindow.show();

		execReturn = app.exec();
	}

	qDebug() << "Ending all render threads";	//xyzm

	OpenGLQuickItem::endAllRenderThreads();

	return execReturn;
}
