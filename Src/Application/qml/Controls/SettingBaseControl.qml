//==================================================================================================================|
// Created 2015.03.12 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0

Item {
    id: root

    property int settingsKey: 0
    property string title: ""

    QtObject {
        id: internal
        property bool loaded: false
    }

    function load() {
        //slider.value = appSettings.value(settingsKey);
        assignFromSettingsValue(appSettings.value(settingsKey));
        internal.loaded = true;
    }

    function save() {
        if (internal.loaded) {
            appSettings.enqueueValue(settingsKey, provideSettingsValue())
            //appSettings.enqueueValue(settingsKey, slider.value);
            appSettings.applyQueuedValues();
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.4
    }

    Component.onCompleted: {
        load();
    }
}
