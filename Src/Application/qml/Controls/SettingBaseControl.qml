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

    width: parent.width

    property int settingsKey: 0
    property string title: ""

    QtObject {
        id: internal
        property bool loaded: false
    }

    function load() {
        console.log("Load called");
        assignFromSettingsValue(appSettings.value(settingsKey));
        internal.loaded = true;
    }

    function save() {
        if (internal.loaded) {
            console.log("Save called");
            appSettings.enqueueValue(settingsKey, provideSettingsValue())
            appSettings.applyQueuedValues();
        }
    }

    property var titleText: text

    Text {
        id: text
        x: 8
        y: 8
        width: 150
        height: 14
        text: root.title
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }

    Component.onCompleted: {
        load();
    }
}
