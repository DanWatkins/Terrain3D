//==================================================================================================================|
// Created 2014.12.11 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_SETTINGS_H
#define _t3d_SETTINGS_H

#include <QtCore/QSettings>

class Settings
{
public:
	Settings() = delete;
	static void init();

private:
	Q_DISABLE_COPY(Settings)

	static QSettings *mSettings;
	static const QString mVersion;
};

#endif

