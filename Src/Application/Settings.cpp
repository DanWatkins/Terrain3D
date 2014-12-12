//==================================================================================================================|
// Created 2014.12.11 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Settings.h"
#include <QtCore/QDir>

QSettings *Settings::mSettings = nullptr;
const QString Settings::mVersion = "0.0.0";

void Settings::init()
{
	QString filepath = QDir::currentPath()+"/Terrain3D.ini";
	mSettings = new QSettings(filepath, QSettings::IniFormat);
	mSettings->setValue("Version", mVersion);
	mSettings->sync();
}


void Settings::setValue(Key key, const QVariant &value)
{
	qDebug() << "Setting value " << value << "for key " << static_cast<int>(key);
}


QVariant Settings::value(Key key)
{
	return QVariant("Very Cool Text");
}
