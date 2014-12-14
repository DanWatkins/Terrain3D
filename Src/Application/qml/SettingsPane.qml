import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import "./Settings"

Item {
    id: root

    Rectangle {
        anchors.fill: parent

        color: "black"
        opacity: 0.45
    }


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
            function saveAll() {
                tab_graphics.saveAll();
                pane_world.saveAllSettings();
            }

            id: tabView
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 10
            height: 360

            Tab {
                id: tab_graphics
                title: "Graphics"
                Graphics { id: pane_graphics }

                function saveAll() {
                    pane_graphics.saveAllSettings();
                }
            }

            Tab {
                title: "World"
                World { id: pane_world }
            }

            Controls {}
        }

        Button {
            id: button_confirm
            x: 10
            y: 376
            width: 75
            height: 36
            text: qsTr("OK")

            onClicked: {
                tab_graphics.saveAll();
                root.destroy();
            }
        }

        Button {
            id: button_cancel
            x: 91
            y: 376
            width: 75
            height: 36
            text: qsTr("Cancel")

            onClicked: root.destroy();
        }
    }
}
