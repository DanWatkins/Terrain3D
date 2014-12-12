//==================================================================================================================|
// Created 2014.12.11 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_SETTINGS_H
#define _t3d_SETTINGS_H

#include <QtCore/QSettings>
#include "Main.h"

class Settings : public QObject
{
	Q_OBJECT

public:
	Settings() {}
	static void init();

	enum Key
	{
		KeyShowHud
	}; Q_ENUMS(Key)


	Q_INVOKABLE static void setValue(Key key, const QVariant &value);
	Q_INVOKABLE static QVariant value(Key key);

private:
	Q_DISABLE_COPY(Settings)

	static QSettings *mSettings;
	static const QString mVersion;

	static QString stringNameForKey(Key key);
};

#endif

