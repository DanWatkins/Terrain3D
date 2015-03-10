//==================================================================================================================|
// Created 2014.12.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include "Settings.h"

#include <QtCore/QDir>
#include <QtCore\QMetaEnum>

void Settings::init()
{
	initDefaultValues();
	checkForMissingMetaKeyInfoValues();

	QString filepath = QDir::currentPath()+"/Terrain3D.ini";
	mSettings = new QSettings(filepath, QSettings::IniFormat);
	mSettings->setValue("Version", mVersion);
	mSettings->sync();
}


void Settings::setValue(Key key, const QVariant &newValue)
{
	QString name = stringNameForKey(key);

	if (value(key) != newValue)
	{
		qDebug() << "Settings value changed for key=" << name
				 << " value=" << newValue.toString();
		mSettings->setValue(name, newValue);

		for (auto listener : mListeners)
			listener->settingsValueChanged(key, newValue);
	}

	mSettings->sync();
}


QVariant Settings::value(Key key)
{
	QVariant value = mSettings->value(stringNameForKey(key),
									  mMetaKeyInfo[key].defaultValue);

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


void Settings::applyQueuedValues()
{
	for (auto i : mSettingsQueue)
		setValue(i.first, i.second);

	mSettingsQueue.clear();
}


void Settings::applyQueuedValuesNoNotify()
{
	QList<SettingsListener*> old = mListeners;
	mListeners.clear();

	applyQueuedValues();

	mListeners = old;
}


bool Settings::containsQueuedValueRequiringRestart()
{
	for (auto keyValuePair : mSettingsQueue)
	{
		if (mMetaKeyInfo[keyValuePair.first].requiresRestart)
			return true;
	}

	return false;
}


void Settings::enqueueValue(Key key, const QVariant &newValue)
{
	//verify the value is actually different than what is currently stored
	if (value(key) != newValue)
		mSettingsQueue.push_back(QPair<Key, QVariant>(key, newValue));
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
	#define d mMetaKeyInfo

	//graphics
	d[GraphicsScreenResolutionWidth] = {800, false};
	d[GraphicsScreenResolutionHeight] = {600, false};
	d[GraphicsScreenIsFullscreen] = {false, false};
	d[GraphicsCameraPositionX] = {0.0f, false};
	d[GraphicsCameraPositionY] = {0.0f, false};
	d[GraphicsCameraPositionZ] = {0.0f, false};
	d[GraphicsCameraFOV] = {50.0f, false};
	d[GraphicsCameraLOD] = {1.0f, false};
	d[GraphicsCameraIVD] = {70.0f, false};
	d[GraphicsCameraWireframe] = {false, false};

	//world
	d[WorldGeneratorSize] = {128, true};
	d[WorldGeneratorTextureMapResolution] = {2, true};
	d[WorldGeneratorFaultCount] = {250, true};
	d[WorldGeneratorSeed] = {0, true};
	d[WorldGeneratorSmoothing] = {0.65, true};
	d[WorldTerrainSpacing] = {1.0f, true};
	d[WorldTerrainHeightScale] = {30.0f, true};
	d[WorldTerrainChunkSize] = {32, true};
	d[WorldTerrainSpanSize] = {8, true};
	d[WorldTerrainLightIntensity] = {18, true};

	#undef d
}


void Settings::checkForMissingMetaKeyInfoValues()
{
	const QMetaObject &mo = Settings::staticMetaObject;
	QMetaEnum me = mo.enumerator(mo.indexOfEnumerator("Key"));

	for (int i=0; i<me.keyCount(); i++)
	{
		Key key = static_cast<Key>(me.value(i));

		if (!mMetaKeyInfo.contains(key))
		{
			QString msg = (QString("Settings: No default value defined for key ")
							+ me.valueToKey(key) + " at:"
							+ QString(__FILE__));

			qFatal(msg.toStdString().c_str());
		}
	}
}