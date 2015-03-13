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

    function assignFromSettingsValue(value) {
        checkBox.checked = value;
    }

    function provideSettingsValue() {
        return checkBox.checked;
    }

    CheckBox {
        id: checkBox
        text: ""
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: titleText.right
        anchors.margins: 6
        onClicked: {
            root.save();
        }
    }
}
