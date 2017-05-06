//==================================================================================================================|
// Created 2015.03.12 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

SettingBaseControl {
    id: root

    height: 30

    default property alias value: slider.value
    property real minimumValue: 0
    property real maximumValue: 100
    property real stepSize: 2
    property bool tickmarksEnabled: false

    function assignFromSettingsValue(value) {
        slider.value = value;
    }

    function provideSettingsValue() {
        return slider.value;
    }

    Slider {
        id: slider
        anchors.right: valueText.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: titleText.right
        anchors.margins: 6

        minimumValue: root.minimumValue
        maximumValue: root.maximumValue
        stepSize: root.stepSize
        tickmarksEnabled: root.tickmarksEnabled

        onValueChanged: {
            root.userChangedValue();
        }
    }


    Text {
        id: valueText
        y: 8
        height: 14
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 12

        text: slider.value.toFixed(2)

        anchors.right: parent.right
        anchors.rightMargin: 6
        anchors.left: parent.right
        anchors.leftMargin: -30
    }
}
