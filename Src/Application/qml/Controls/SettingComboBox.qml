//==================================================================================================================|
// Created 2015.03.11 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0

SettingBaseControl {
    id: root

    height: 30

    property var model: null

    function assignFromSettingsValue(value) {
        comboBox.currentIndex = comboBox.find(value);
    }

    function provideSettingsValue() {
        return comboBox.currentText;
    }

    ComboBox {
        id: comboBox
        anchors.right: parent.right
        anchors.rightMargin: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.left: text.right
        anchors.leftMargin: 6

        model: root.model

        onCurrentTextChanged: {
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
}
