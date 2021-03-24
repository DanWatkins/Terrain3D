//==================================================================================================================|
// Created 2014.12.06 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <QtCore/QThread>

namespace t3d
{

class BackgroundUpdater : public QThread
{
    Q_OBJECT
public:
    BackgroundUpdater() : mFrequencyMs(16) {}
    BackgroundUpdater(int frequencyMs) : mFrequencyMs(frequencyMs) {}

protected:
    void run() override
    {
        while (isInterruptionRequested() == false)
        {
            msleep(mFrequencyMs);
            emit needsUpdate();
        }
    }

private:
    int mFrequencyMs;

signals:
    void needsUpdate();
};

}
