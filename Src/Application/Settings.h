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
	Settings() {}

	/**
	 * @brief Loads the settings from file and creates a table of default values.
	 * Should be called once at the begining before any QApplications exist.
	 */
	static void init();

	enum Key
	{
		KeyShowHud,

		//renderer
		KeyWireframe
	}; Q_ENUMS(Key)

	/**
	 * @brief Assigns \p value to be associated with \p key.
	 *
	 * @param key The key to associate with
	 * @param value The value to associate with
	 */
	Q_INVOKABLE static void setValue(Key key, const QVariant &newValue);

	/**
	 * @returns The value associated with \p key. If the key does not exists, a
	 * default value is returned.
	 *
	 * @param key The key to find a value for
	 */
	static QVariant value(Key key);
	Q_INVOKABLE static bool boolValue(Key key);

	/**
	 * @brief Adds \p listener to a list. All delegate methods are called
	 * as documented.
	 * @param listener The listener to add
	 */
	static void addListener(SettingsListener *listener);

	/**
	 * @brief Removes \p listener from the list of listeners.
	 *
	 * @param listener The listener to be removed
	 */
	static void removeListener(SettingsListener *listener);

private:
	Q_DISABLE_COPY(Settings)

	static QSettings *mSettings;
	static const QString mVersion;
	static QHash<Key, QVariant> mDefaultValues;
	static QList<SettingsListener*> mListeners;

	static QString stringNameForKey(Key key);
	static void initDefaultValues();
	static void checkForMissingDefaultValues();
};

class SettingsListener
{
public:
	/**
	 * @brief Called whenever a Settings value is changed. It is also called
	 * when the setting is loaded for the first time during application statup.
	 *
	 * @param key The key this value represents
	 * @param newValue The current value
	 * @param oldValue The value before before the new value
	 */
	virtual void settingsValueUpdated(Settings::Key key,
									  const QVariant &newValue,
									  const QVariant &oldValue) = 0;
};

#endif
