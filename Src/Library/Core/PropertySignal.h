//==================================================================================================================|
// Created 2015.03.18 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _PropertySignal_h
#define _PropertySignal_h

#include <QtCore/QObject>
#include <functional>

/**
 * A proxy type fro Property because Qt doesn't support template QObject derived classes.
 */
class PropertySignal : public QObject
{
	Q_OBJECT

public:
	void sendEmit() { emit valueChanged(); }

	void connectToOnChanged(std::function<void(void)> observerFunction)
	{
		QObject::connect(this, &PropertySignal::valueChanged, observerFunction);
	}

signals:
	void valueChanged();
};

#endif
