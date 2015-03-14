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
    }


    /**
     * Loads the actual setting value from storage and assigns it to the
     * specialized control.
     */
    function load() {
        assignFromSettingsValue(appSettings.value(settingsKey));
        titleText.color = "black"
        internal.loaded = true;
    }


    /**
     * Should be called by specialized Setting controls whenever the control's
     * value is changed by the user.
     */
    function userChangedValue() {
        if (internal.loaded) {
            if (appSettings.updateTypeForKey(settingsKey) === Settings.Instant) {
                internal.flagText();
                appSettings.setValue(settingsKey, provideSettingsValue());
                animateOutFlagText();
            }
            else {
                internal.flagText();
                appSettings.enqueueValue(settingsKey, provideSettingsValue());
            }
        }
    }


    /**
     * (Re)starts a color animation to transition from a red title text to black.
     */
    function animateOutFlagText() {
        if (Qt.colorEqual(titleText.color, "red")) {
            titleText.flagAnimation.duration = 1500;

            if (titleText.flagAnimation.running)
                titleText.flagAnimation.stop();

            titleText.flagAnimation.start();
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

        property var flagAnimation: flagAnimation

        ColorAnimation on color {
            id: flagAnimation
            to: "black"
        }
    }


    Component.onCompleted: {
        load();
    }
}
