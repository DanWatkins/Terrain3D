//==================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Application.h"
#include "Terrain3D.h"
#include "Settings.h"

#include <QuickItems/CameraItem.h>

#include <QOpenGLContext>

Settings mainSettings;

/**
 * Launches a Terrain3D window instance. Blocks until the instance finishes. The
 * instance may request to be restarted which will cause further blocking until
 * the new instance finishes and does not restart again.
 */
void loadAndRun(QGuiApplication &app)
{
	bool restart = true;
	int instanceCount = 0;

	while (restart)
	{
		if (instanceCount == 0)
			qDebug() << "Starting new instance..";
		else
			qDebug() << "Restarting...";

		++instanceCount;

		t3d::Terrain3D mainWindow(&mainSettings);

        QSurfaceFormat format;
        format.setMajorVersion(4);
        format.setMinorVersion(1);
        format.setProfile(QSurfaceFormat::CoreProfile);
        mainWindow.setFormat(format);

		mainWindow.rootContext()->setContextProperty("appSettings", &mainSettings);
		mainWindow.rootContext()->setContextProperty("terrain3D", &mainWindow);

		mainWindow.init();

		Q_UNUSED(app); // apparently MSVC freaks out on /w4 claiming app is never referenced...
		app.exec();
		restart = mainWindow.needsRestart();
	}
}


int main(int argc, char *argv[])
{
    /*AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);*/

	QGuiApplication app(argc, argv);
	mainSettings.init();

	//set all the QuickItem types
	{
		using namespace t3d::QuickItems;

		qmlRegisterType<CameraItem>("Terrain3D", 1, 0, "Camera");
		qmlRegisterType<Settings>("Terrain3D", 1, 0, "Settings");
	}

	loadAndRun(app);

	return 0;
}
