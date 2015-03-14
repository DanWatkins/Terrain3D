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
        settings_graphics.load();
        settings_world.load();
    }

    function refreshIfNeeded() {
        if (visible) {
            settings_graphics.load();
            settings_world.load();
        }
    }

    //the main settings pane
    Rectangle {
        id: rectPane
        anchors.fill: parent

        color: "#ffffff"
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: -20
        opacity: 0.80

        ColumnLayout {
            id: sidePane
            anchors.fill: parent
            anchors.margins: 5

            Layout.alignment: Qt.AlignTop

            Graphics {
                id: settings_graphics
                Layout.fillWidth: true
            }

            World {
                id: settings_world
                Layout.fillWidth: true
            }

            Item {  //fill remaining vertical space
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }	


        RowLayout {
			id: confirmBar
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
                    root.saveSettings();
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
        }
    }
}
