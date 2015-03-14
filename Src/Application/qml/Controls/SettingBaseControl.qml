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

        function flagText() {
            titleText.color = "red";
        }

        function animateOutFlagText() {
            console.log("TODO We need to animate to black");
            titleText.color = "black";
        }
    }

    function load() {
        assignFromSettingsValue(appSettings.value(settingsKey));
        internal.loaded = true;
    }

    function userChangedValue() {
        if (internal.loaded) {
            if (appSettings.updateTypeForKey(settingsKey) === Settings.Instant) {
                console.log("vagina");
                internal.flagText();
                appSettings.setValue(settingsKey, provideSettingsValue());
                internal.animateOutFlagText();
            }
            else {
                console.log("dick");
                internal.flagText();
                appSettings.enqueueValue(settingsKey, provideSettingsValue());
            }
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
