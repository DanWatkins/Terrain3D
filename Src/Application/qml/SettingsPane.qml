import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import "./Settings"

Item {
    Rectangle {
        anchors.fill: parent

        color: "black"
        opacity: 0.35
    }


    Rectangle {
        anchors.centerIn: parent
        width: 600
        height: 420

        color: "#beae98"
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: -20
        opacity: 0.85

        TabView {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 10
            height: 360

            Controls {

            }

            Graphics {

            }

            World {

            }
        }

        Button {
            id: button1
            x: 10
            y: 376
            width: 75
            height: 36
            text: qsTr("OK")
        }

        Button {
            id: button2
            x: 91
            y: 376
            width: 75
            height: 36
            text: qsTr("Cancel")
        }
    }
}
