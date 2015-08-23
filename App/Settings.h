//==================================================================================================================|
// Created 2014.12.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_Settings_H
#define _t3d_Settings_H

#include <QtCore/QSettings>
#include <QtCore/QHash>

#include <Application.h>

class SettingsListener;

class Settings : public QObject
{
	Q_OBJECT

public:
	/**
	 * @brief The default constructor.
	 */
	Settings() :
		mSettings(nullptr),
		mVersion("0.0.0")
	{}

	/**
	 * @brief Loads the settings from file and creates a table of default values.
	 * Should be called once at the begining before any QApplications exist.
	 */
	void init();

	enum Key
	{
		//graphics
		GraphicsScreenResolutionWidth		= 100,
		GraphicsScreenResolutionHeight		= 101,
		GraphicsScreenIsFullscreen			= 102,
		GraphicsCameraPositionX				= 103,
		GraphicsCameraPositionY				= 104,
		GraphicsCameraPositionZ				= 105,
        GraphicsCameraFOV					= 110,  /* Field of view: Degrees measurment of the camera's viewing angle */
        GraphicsCameraLODFactor 			= 111,  /* Level of detail: A scale factor to adjust the overall level of detail */
        GraphicsCameraLODNear				= 112,	/* The forward distance from the camera at which point the LOD begins to interpolate towards LODFar */
        GraphicsCameraLODFar                = 113,  /* The forward distance from the camera at which point the LODNear has interpolated to the lowest LOD */
        GraphicsCameraWireframe				= 130,

		//world
		WorldGeneratorSize					= 201,
		WorldGeneratorTextureMapResolution	= 202,
		WorldGeneratorSeed					= 203,
		WorldGeneratorFaultCount			= 204,
		WorldGeneratorSmoothing				= 205,
		WorldTerrainHeightScale				= 211,
		WorldTerrainChunkSize				= 212,
		WorldTerrainSpanSize				= 213,
		WorldTerrainLightIntensity			= 214
	}; Q_ENUMS(Key)

	enum KeyUpdateType
	{
		Instant,
		Queued
	}; Q_ENUMS(KeyUpdateType)

	/**
	 * @brief Assigns \p value to be associated with \p key. The internal QSettings
	 * instance is also synced.
	 *
	 * @param key The key to associate with
	 * @param value The value to associate with
	 */
	Q_INVOKABLE void setValue(Key key, const QVariant &newValue);

	/**
	 * @returns The value associated with \p key. If the key does not exists, a
	 * default value is returned.
	 *
	 * @param key The key to find a value for
	 */
	Q_INVOKABLE QVariant value(Key key);

	/**
	 * @brief Adds \p listener to a list. All delegate methods are called
	 * as documented.
	 * @param listener The listener to add
	 */
	void addListener(SettingsListener *listener);

	/**
	 * @brief Removes \p listener from the list of listeners.
	 *
	 * @param listener The listener to be removed
	 */
	void removeListener(SettingsListener *listener);

	/**
	 * @brief Each key/value enqueued with enqueueValue() is applied to the
	 * settings by calls to setValue().
	 */
	Q_INVOKABLE void applyQueuedValues();


	/**
	 * @brief Removes all queued settings from the settings queue.
	 */
	Q_INVOKABLE void clearQueuedValues() { mSettingsQueue.clear(); }

	/**
	 * Enques the \p key and \p value in a temporary queue which can later be
	 * be applied using applyQueuedValues().
	 */
	Q_INVOKABLE void enqueueValue(Key key, const QVariant &newValue);

	/**
	 * @returns the KeyUpdateType associated with the specified key
	 */
	Q_INVOKABLE KeyUpdateType updateTypeForKey(Key key) { return mMetaKeyInfo[key].updateType; }

private:
	Q_DISABLE_COPY(Settings)

	QSettings *mSettings;
	const QString mVersion;
	QList<SettingsListener*> mListeners;
	QList<QPair<Key, QVariant>> mSettingsQueue;

	struct MetaKeyInfo
	{
		QVariant defaultValue;
		KeyUpdateType updateType;
	};

	QHash<Key, MetaKeyInfo> mMetaKeyInfo;

	QString stringNameForKey(Key key);
	void initDefaultValues();
	void checkForMissingMetaKeyInfoValues();
};


class SettingsListener
{
public:
	virtual void settingsValueChanged(Settings::Key key, const QVariant &value) = 0;
	virtual void settingsQueueFinishedApplying() = 0;
};

#endif
