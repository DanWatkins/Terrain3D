//==================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>

#include "Main.h"
#include <Terrain3DX.h>

#include <QuickItems/Camera.h>

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	//set all the QuickItem types
	{
		using namespace t3d::QuickItems;

		qmlRegisterType<Camera>("Terrain3DX", 1, 0, "Camera");
	}


	int execReturn = 0;
	{
		QQuickView view;

		QSurfaceFormat format;
		format.setMajorVersion(4);
		format.setMinorVersion(2);
		format.setProfile(QSurfaceFormat::CompatibilityProfile);
		view.setFormat(format);

		view.setPersistentOpenGLContext(true);
		view.setPersistentSceneGraph(true);

		view.setResizeMode(QQuickView::SizeRootObjectToView);
		view.setSource(QUrl("qrc:///main.qml"));
		view.show();

		execReturn = app.exec();
	}

	OpenGLQuickItem::endAllRenderThreads();

	return execReturn;
}



/* OLD MAIN.CPP
#include "Main.h"
#include <Terrain3D.h>

using namespace t3d;

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	QSurfaceFormat format;
	format.setSamples(16);

	Terrain3D window;
	window.setFormat(format);
	window.resize(1600, 900);
	window.show();

	window.setAnimating(true);

	return app.exec();
}
*/
