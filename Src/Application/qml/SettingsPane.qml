//==================================================================================================================|
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0

import "./Settings"
import "./Controls"

Item {
    id: root

    anchors.left: parent.left
    anchors.top: parent.top
    anchors.bottom: parent.bottom

    width: 300

    signal hasFinished()

    //dim the whole screen
    Rectangle {
        anchors.fill: parent

        color: "black"
        opacity: 0.45
    }

    function loadSettings() {
        console.log("loading settings from the settings pane");
        rectPane.loadAllSettings();
    }

    function refreshIfNeeded() {
        if (visible)
            loadSettings();
    }

    //the main settings pane
    Rectangle {
        id: rectPane
        anchors.fill: parent

        color: "#ffffff"
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: -20
        opacity: 0.80

        function loadAllSettings() {
            paneGraphics.loadSettings();
            paneWorld.loadSettings();
        }

        function saveAllSettings() {
            paneGraphics.saveSettings();
            paneWorld.saveSettings();
        }

        ColumnLayout {
            id: columnLayout1
            anchors.fill: parent
            anchors.margins: 5

            Graphics {
                id: paneGraphics
                Layout.fillWidth: parent
            }


            World {
                id: paneWorld
                Layout.fillWidth: parent
            }
        }

        RowLayout {
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            Button {
                id: button_confirm

                Layout.fillHeight: parent
                Layout.fillWidth: parent
                text: qsTr("Apply")

                onClicked: {
                    parent.saveAllSettings();
                    var needsRestart = appSettings.containsQueuedValueRequiringRestart();

                    if (needsRestart) {
                        appSettings.applyQueuedValuesNoNotify();
                        terrain3D.requestRestart();
                    }
                    else {
                        appSettings.applyQueuedValues();
                    }

                    root.visible = false;
                    hasFinished();
                }
            }

            Button {
                id: button_cancel
                Layout.fillHeight: parent
                Layout.fillWidth: parent
                text: qsTr("Cancel")

                onClicked: {
                    root.visible = false;
                    hasFinished();
                }
            }

            SettingComboBox {
                title: "Size:"
                settingsKey: Settings.WorldTerrainChunkSize
                model: [8, 16, 32, 64, 128, 256]
            }
        }
    }
}
