//==================================================================================================================|
// Created 2014.12.11 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_SETTINGS_H
#define _t3d_SETTINGS_H

#include <QtCore/QSettings>
#include <QtCore/QHash>

#include "Main.h"

class Settings : public QObject
{
	Q_OBJECT

public:
	Settings() {}	//this is only here so QML can use it
	static void init();

	enum Key
	{
		KeyShowHud,
		KeyFullscreen
	}; Q_ENUMS(Key)

	Q_INVOKABLE static void setValue(Key key, const QVariant &value);
	Q_INVOKABLE static QVariant value(Key key);

private:
	Q_DISABLE_COPY(Settings)

	static QSettings *mSettings;
	static const QString mVersion;
	static QHash<Key, QVariant> mDefaultValues;

	static QString stringNameForKey(Key key);
	static void initDefaultValues();
	static void checkForMissingDefaultValues();
};

#endif
