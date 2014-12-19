import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0


Item {
    id: appWindow
    width: 800
    height: 600

    Rectangle {
        anchors.fill: parent

        Camera {
            id: mainCamera
            objectName: "t3d_mainCamera"
            anchors.fill: parent


            transform: Scale { origin.y: 300; yScale: -1.0 }

                /*Rotation {
                            origin { x: 800/2; y: 600/2 }
                            axis { x: 1; y: 1; z: 0 }
                            angle: 180
                        }*/

            /*onIsLoadedChanged: {
                console.log("DOING hgasklgsdlg");
                menuButtons.visible = true;
            }*/
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
        }
    }
}
