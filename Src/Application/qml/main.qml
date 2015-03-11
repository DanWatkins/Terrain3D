import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0


Item {
    id: appWindow
    width: 800
    height: 600


    Camera {
        id: mainCamera
        objectName: "t3d_mainCamera"
		anchors.fill: parent

        //we have to flip the image vertically since the FBO is upside down
        transform: Scale { origin.y: height/2; yScale: -1.0 }

        onIsLoadedChanged: {
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
        settingsPane.item.refreshIfNeeded();
        mainCamera.isFrozen = settingsPane.item.visible;
    }


    Connections {
        target: settingsPane.item
        onHasFinished: {
            mainCamera.isFrozen = false;
        }
    }

    Connections {
        target: terrain3D
        onToggleSettingsMenu: toggleSettingsPane();
        onRefreshSettingsMenu: settingsPane.item.refreshIfNeeded();
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
                onClicked: {
                    terrain3D.toggleCaptureCursor();
                    settingsPane.item.refreshIfNeeded();
                }
            }
            Button {
                id: button_restart
                text: "Restart (F5)"
                height: 30
                onClicked: terrain3D.requestRestart();
            }
			Button {
                id: button_reloadShaders
                text: "Realod Shaders (F6)"
                height: 30
                onClicked: terrain3D.reloadShaders();
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
                onClicked: {
                    terrain3D.toggleFullscreen();
                    settingsPane.item.refreshIfNeeded();
                }
            }
            Button {
                id: button_exit
                text: "Exit (Esc)"
                height: 30
                onClicked: terrain3D.close();
            }

            Text {
                text: "FPS: " + Math.min(terrain3D.fps, 60);
                font.pointSize: 16
                color: "white"
            }

            Text {
                text: "Pos: " + terrain3D.cameraPos;
                font.pointSize: 16
                color: "white"
            }
        }
    }
}
