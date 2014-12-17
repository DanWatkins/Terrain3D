import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0

Terrain3DWindow {
    id: appWindow

    Camera {
        id: mainCamera
        y: 40
        objectName: "t3d_mainCamera"
        anchors.fill: parent
        anchors.margins: 0

        onIsLoadedChanged: {
            console.log("DOING hgasklgsdlg");
            menuButtons.visible = true;
        }
    }

    Loader {
        id: settingsPane
        anchors.fill: parent
        anchors.centerIn: parent
        //asynchronous: true

        onLoaded: {
            settingsPane.item.loadSettings();
        }
    }

    Connections {
        target: settingsPane.item
        onHasFinished: {
            settingsPane.sourceComponent = null;
        }
    }

    Item {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 50

        Rectangle {
            anchors.fill: parent
            color: "black"
            opacity: 0.65
        }

        RowLayout {
            id: menuButtons
            x: 10
            y: 10
            spacing: 10

            width: Layout.minimumWidth
            height: Layout.minimumHeight

            Button {
                id: button_exit
                text: "Exit (Esc)"
                height: 30
                onClicked: terrain3D.close();
            }
            Button {
                id: button_captureCursor
                text: "Capture Cursor (F1)"
                height: 30
                onClicked: console.log("Implement me dork");
            }
            Button {
                id: button_restart
                text: "Restart (F5)"
                height: 30
                onClicked: terrain3D.restart();
            }
            Button {
                id: button_settings
                text: "Settings (F10)"
                height: 30
                onClicked: settingsPane.source = "SettingsPane.qml"
            }
            Button {
                id: button_fullscreen
                text: "Fullscreen (F11)"
                height: 30
                onClicked: terrain3D.toggleFullscreen();
            }
        }
    }
}
