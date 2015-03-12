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
        text: title
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 8

        onClicked: {
            root.save();
        }
    }
}
