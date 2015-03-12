//==================================================================================================================|
// Created 2015.03.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

//import Terrain3D 1.0

Item {
    id: root

    width: 200
    height: 30

    property int settingsKey: 0
    property string title: ""

    property real minimumValue: 0
    property real maximumValue: 100
    property real stepSize: 2
    property bool tickmarksEnabled: false


    QtObject {
        id: internal
        property bool loaded: false
    }

    function load() {
        slider.value = appSettings.value(settingsKey);
        internal.loaded = true;
    }

    function save() {
        if (internal.loaded) {
            appSettings.enqueueValue(settingsKey, slider.value);
            appSettings.applyQueuedValues();
        }
    }

    Slider {
        id: slider
        anchors.right: valueText.left
        anchors.rightMargin: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.left: text.right
        anchors.leftMargin: 6

        minimumValue: root.minimumValue
        maximumValue: root.maximumValue
        stepSize: root.stepSize
        tickmarksEnabled: root.tickmarksEnabled

        onValueChanged: {
            root.save();
        }
    }

    Text {
        id: text
        x: 8
        y: 8
        width: 100
        height: 14
        text: root.title
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }


    Text {
        id: valueText
        y: 8
        height: 14
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 12

        text: slider.value

        anchors.right: parent.right
        anchors.rightMargin: 6
        anchors.left: parent.right
        anchors.leftMargin: -40
    }

    Component.onCompleted: {
        load();
    }
}
