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


void Settings::applyQueuedValuesNoNotify()	//TODO this method is useless now
{
	QList<SettingsListener*> old = mListeners;
	mListeners.clear();

	applyQueuedValues();

	mListeners = old;
}


void Settings::enqueueValue(Key key, const QVariant &newValue)
{
	if (mMetaKeyInfo[key].updateType != KeyUpdateType::Queued)
	{
		QString message = "Warning: Attempting to queue a non-queued setting key="+QString::number(static_cast<int>(key))
			+ ", value="+newValue.toString();
		qWarning(message.toStdString().c_str());
	}

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
	d[GraphicsScreenResolutionWidth] = {800, Instant};
	d[GraphicsScreenResolutionHeight] = {600, Instant};
	d[GraphicsScreenIsFullscreen] = {false, Instant};
	d[GraphicsCameraPositionX] = {0.0f, Instant};
	d[GraphicsCameraPositionY] = {0.0f, Instant};
	d[GraphicsCameraPositionZ] = {0.0f, Instant};
	d[GraphicsCameraFOV] = {60.0f, Instant};
	d[GraphicsCameraLOD] = {1.0f, Instant};
	d[GraphicsCameraIVD] = {140.0f, Instant};
	d[GraphicsCameraWireframe] = {false, Instant};

	//world
	d[WorldGeneratorSize] = {256, Queued};
	d[WorldGeneratorTextureMapResolution] = {1, Queued};
	d[WorldGeneratorFaultCount] = {300, Queued};
	d[WorldGeneratorSeed] = {0, Queued};
	d[WorldGeneratorSmoothing] = {0.70, Queued};
	d[WorldTerrainHeightScale] = {30.0f, Instant};
	d[WorldTerrainChunkSize] = {64, Instant};
	d[WorldTerrainSpanSize] = {16, Instant};
	d[WorldTerrainLightIntensity] = {18, Queued};

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