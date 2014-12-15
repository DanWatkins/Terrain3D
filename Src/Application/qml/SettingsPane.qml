import QtQuick 2.3
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

    //the main settings pane
    Rectangle {
        anchors.centerIn: parent
        width: 600
        height: 420

        color: "#4a65a3"
        radius: 6
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: -20
        opacity: 0.85

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
                Graphics {}
            }

            Tab {
                id: tab_world
                title: "World"
                active: true
                World {}
            }

            Tab {
                id: tab_controls
                title: "Controls"
                active: true
                Controls {}
            }


            function saveAll() {
                tab_graphics.item.saveAllSettings();
                tab_world.item.saveAllSettings();
                tab_controls.item.saveAllSettings();
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
                tabView.saveAll();
                //root.hasFinished();
            }
        }

        Button {
            id: button_cancel
            x: 91
            y: 376
            width: 75
            height: 36
            text: qsTr("Cancel")

            onClicked: root.hasFinished();
        }
    }
}
