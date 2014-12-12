//==================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <QtGui/QGuiApplication>
#include <QtCore/QSettings>

#include "Main.h"
#include "Terrain3D.h"
#include "Settings.h"

#include <QuickItems/CameraItem.h>

static QObject* settingsSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
	Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)

	return new Settings();
}

class Listener : public SettingsListener
{
public:
	void settingsValueUpdated(Settings::Key key, const QVariant &newValue,
							  const QVariant &oldValue) override
	{
		qDebug() << "Override called!!!!";
	}
};


int main(int argc, char *argv[])
{	
	QGuiApplication app(argc, argv);
	Settings::init();

	Listener l;
	Settings::addListener(&l);

	//set all the QuickItem types
	{
		using namespace t3d::QuickItems;

		qmlRegisterType<CameraItem>("Terrain3D", 1, 0, "Camera");
		qmlRegisterSingletonType<Settings>("Terrain3D.Settings", 1, 0,
								 "MySettings",
								 settingsSingletonProvider);
	}

	int execReturn = 0;
	{
		t3d::Terrain3D mainWindow;
		mainWindow.init();
		mainWindow.show();

		execReturn = app.exec();
	}

	qDebug() << "Ending all render threads";	//xyzm

	t3d::OpenGLQuickItem::endAllRenderThreads();

	return execReturn;
}
