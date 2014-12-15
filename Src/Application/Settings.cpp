//==================================================================================================================|
// Created 2014.12.11 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Settings.h"

#include <QtCore/QDir>
#include <QMetaEnum>

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


void Settings::applyQueuedValues()
{
	qDebug() << "Applying queued values";

	for (auto i : mSettingsQueue)
		setValue(i.first, i.second);

	mSettingsQueue.clear();
}


void Settings::setValue(Key key, const QVariant &newValue)
{
	QString name = stringNameForKey(key);
	qDebug() << "Setting value " << newValue << "for key " << name;

	QVariant oldValue = value(key);
	for (auto i : mListeners)
		i->settingsValueUpdated(key, newValue, oldValue);

	mSettings->setValue(name, newValue);
}


void Settings::enqueueValue(Key key, const QVariant &newValue)
{
	//qDebug() << "Enqueing setting: " << stringNameForKey(key) << " " << newValue;
	mSettingsQueue.push_back(QPair<Key, QVariant>(key, newValue));
}



QVariant Settings::value(Key key)
{
	QVariant value = mSettings->value(stringNameForKey(key), mDefaultValues[key]);
	qDebug() << "Returning value " << value << " " << value.typeName();

	if (QString(value.typeName()) == "QString" &&
		(value.toString() == "false" || value.toString() == "true"))
		return QVariant(value.toBool());

	return value;
}


void Settings::addListener(SettingsListener *listener)
{
	if (listener != nullptr  &&  !mListeners.contains(listener))
		mListeners.push_back(listener);
}


void Settings::removeListener(SettingsListener *listener)
{
	mListeners.removeOne(listener);
}

///// PRIVATE

QString Settings::stringNameForKey(Key key)
{
	const QMetaObject &mo = Settings::staticMetaObject;
	QMetaEnum me = mo.enumerator(mo.indexOfEnumerator("Key"));
	return me.valueToKey(key);
}


void Settings::initDefaultValues()
{
	#define d mDefaultValues

	//graphics
	d[GraphicsScreenResolutionWidth] = 800;
	d[GraphicsScreenResolutionHeight] = 600;
	d[GraphicsScreenIsFullscreen] = false;
	d[GraphicsCameraPositionX] = 0.0f;
	d[GraphicsCameraPositionY] = 0.0f;
	d[GraphicsCameraPositionZ] = 0.0f;
	d[GraphicsCameraFOV] = 50.0f;
	d[GraphicsCameraLOD] = 1.0f;
	d[GraphicsCameraWireframe] = false;

	//world
	d[WorldGeneratorSize] = 128;
	d[WorldGeneratorTextureMapResolution] = 2;
	d[WorldGeneratorSeed] = 0;
	d[WorldTerrainSpacing] = 1.0f;
	d[WorldTerrainHeightScale] = 30.0f;
	d[WorldTerrainBlockSize] = 32;
	d[WorldTerrainSpanSize] = 8;

	#undef d
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
							+ me.valueToKey(key) + " at:"
							+ QString(__FILE__) + " "
							+ QString(__func__));

			qFatal(msg.toStdString().c_str());
		}
	}
}
