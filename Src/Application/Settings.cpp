//==================================================================================================================|
// Created 2014.12.11 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Settings.h"

#include <QtCore/QDir>
#include <QMetaEnum>

QSettings *Settings::mSettings = nullptr;
const QString Settings::mVersion = "0.0.0";
QHash<Settings::Key, QVariant> Settings::mDefaultValues;

//TODO man, you need to unit test this

void Settings::init()
{
	initDefaultValues();
	checkForMissingDefaultValues();

	QString filepath = QDir::currentPath()+"/Terrain3D.ini";
	mSettings = new QSettings(filepath, QSettings::IniFormat);
	mSettings->setValue("Version", mVersion);
	mSettings->sync();
}


void Settings::setValue(Key key, const QVariant &value)
{
	QString name = stringNameForKey(key);
	qDebug() << "Setting value " << value << "for key " << name;
	mSettings->setValue(name, value);
}


QVariant Settings::value(Key key)
{
	return mSettings->value(stringNameForKey(key), mDefaultValues[key]);
}


QString Settings::stringNameForKey(Key key)
{
	const QMetaObject &mo = Settings::staticMetaObject;
	QMetaEnum me = mo.enumerator(mo.indexOfEnumerator("Key"));
	return me.valueToKey(key);
}


void Settings::initDefaultValues()
{
	mDefaultValues[KeyShowHud] = true;

	mDefaultValues[KeyWireframe] = true;
}


void Settings::checkForMissingDefaultValues()
{
	const QMetaObject &mo = Settings::staticMetaObject;
	QMetaEnum me = mo.enumerator(mo.indexOfEnumerator("Key"));

	for (int i=0; i<me.keyCount(); i++)
	{
		Key key = static_cast<Key>(me.value(i));

		if (!mDefaultValues.contains(key))
		{
			QString msg = (QString("Settings: No default value defined for key ")
								  + me.valueToKey(key));

			qFatal(msg.toStdString().c_str());
		}
	}
}
