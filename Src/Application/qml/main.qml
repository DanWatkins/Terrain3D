import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0


Item {
    id: appWindow
    width: 800
    height: 600

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
        source:"SettingsPane.qml"
        visible: false

        onLoaded: {
            settingsPane.item.loadSettings();
            settingsPane.item.visible = false;
            visible = true;
        }
    }


    function toggleSettingsPane() {
        settingsPane.item.visible = !settingsPane.item.visible;
    }


    Connections {
        target: settingsPane.item
        onHasFinished: {
            settingsPane.sourceComponent = null;
        }
    }

    Connections {
        target: terrain3D
        onToggleSettingsMenu: toggleSettingsPane();
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
                id: button_captureCursor
                text: "Capture Cursor (F1)"
                height: 30
                onClicked: terrain3D.toggleCaptureCursor();
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
                onClicked: toggleSettingsPane();
            }
            Button {
                id: button_fullscreen
                text: "Fullscreen (F11)"
                height: 30
                onClicked: terrain3D.toggleFullscreen();
            }
            Button {
                id: button_exit
                text: "Exit (Esc)"
                height: 30
                onClicked: terrain3D.close();
            }
        }
    }
}
