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

class SettingsListener;

class Settings : public QObject
{
	Q_OBJECT

public:
	/**
	 * @brief The default constructor is only available for QML. Instantiating
	 * a Settings instance in C++ is pointless.
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
		GraphicsCameraFOV					= 106,
		GraphicsCameraLOD					= 107,
		GraphicsCameraWireframe				= 108,

		//world
		WorldGeneratorSize					= 201,
		WorldGeneratorTextureMapResolution	= 202,
		WorldGeneratorSeed					= 203,
		WorldTerrainSpacing					= 204,
		WorldTerrainHeightScale				= 205,
		WorldTerrainBlockSize				= 206,
		WorldTerrainSpanSize				= 207


	}; Q_ENUMS(Key)

	/**
	 * @brief Assigns \p value to be associated with \p key.
	 *
	 * @param key The key to associate with
	 * @param value The value to associate with
	 */
	void setValue(Key key, const QVariant &newValue);

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
	void clearQueuedValues() { mSettingsQueue.clear(); }

	/**
	 * @returns True if there is a key/value in the queue that requires a
	 * restart for changes to take effect.
	 */
	Q_INVOKABLE bool containsQueuedValueRequiringRestart();

	/**
	 * Enques the \p key and \p value in a temporary queue which can later be
	 * be applied using applyQueuedValues().
	 */
	Q_INVOKABLE void enqueueValue(Key key, const QVariant &newValue);

private:
	Q_DISABLE_COPY(Settings)

	QSettings *mSettings;
	const QString mVersion;
	QList<SettingsListener*> mListeners;
	QList<QPair<Key, QVariant>> mSettingsQueue;

	struct MetaKeyInfo
	{
		QVariant defaultValue;
		bool requiresRestart;
	};

	QHash<Key, MetaKeyInfo> mMetaKeyInfo;

	QString stringNameForKey(Key key);
	void initDefaultValues();
	void checkForMissingMetaKeyInfoValues();
};

class SettingsListener
{
public:
	virtual void settingsUpdated();
};

#endif
