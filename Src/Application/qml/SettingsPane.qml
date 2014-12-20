import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import "./Settings"

Item {
    id: root
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
        anchors.centerIn: parent
        width: 600
        height: 420

        color: "#4a65a3"
        radius: 6
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: -20
        opacity: 0.85

        function loadAllSettings() {
            tab_graphics.item.loadSettings();
            tab_world.item.loadSettings();
            tab_controls.item.loadSettings();
        }

        function saveAllSettings() {
            tab_graphics.item.saveSettings();
            tab_world.item.saveSettings();
            tab_controls.item.saveSettings();
        }

        TabView {
            id: tabView
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 10
            height: 360


            Tab {
                id: tab_graphics
                title: "Graphics"
                active: true
                asynchronous: false
                Graphics {}
            }

            Tab {
                id: tab_world
                title: "World"
                active: true
                asynchronous: false
                World {}
            }

            Tab {
                id: tab_controls
                title: "Controls"
                active: true
                asynchronous: false
                Controls {}
            }
        }

        Button {
            id: button_confirm
            x: 10
            y: 376
            width: 75
            height: 36
            text: qsTr("OK")

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
            x: 91
            y: 376
            width: 75
            height: 36
            text: qsTr("Cancel")

            onClicked: {
                root.visible = false;
                hasFinished();
            }
        }

        Text {
            id: statusText
            x: 172
            y: 388
            width: 418
            height: 13
        }
    }
}
