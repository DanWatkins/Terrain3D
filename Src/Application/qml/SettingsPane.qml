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
        testGroup.load();
    }


    function saveSettings() {
        testGroup.save();
    }

    function refreshIfNeeded() {
        if (visible)
            testGroup.load();
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

            SettingGroupBox {
				id: testGroup
				title: "Test Settings"
				Layout.fillWidth: true

                SettingSpinBox {
                    title: "Chunk Size:"
                    settingsKey: Settings.WorldTerrainChunkSize
                }

                SettingComboBox {
                    title: "Span Size:"
                    settingsKey: Settings.WorldTerrainSpanSize
                }

                SettingSlider {
                    title: "LOD:"
                    settingsKey: Settings.GraphicsCameraLOD

                    minimumValue: 0.1
                    maximumValue: 2.0
                    stepSize: 0.05
                    tickmarksEnabled: true
                }

                SettingCheckBox {
                    title: "Fullscreen"
                    settingsKey: Settings.GraphicsScreenIsFullscreen
                }

                Component.onCompleted: {
                    console.log("We just did the column");
                }
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
