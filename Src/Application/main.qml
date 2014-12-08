import QtQuick.Controls 1.2

import Terrain3D 1.0

Terrain3DWindow {
    Camera {
        id: mainCamera
        y: 40
        objectName: "t3d_mainCamera"
        anchors.fill: parent
        anchors.margins: 0
    }

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "New"
                shortcut: "Ctrl+N"
            }
            MenuItem {
                text: "Open"
                shortcut: "Ctrl+O"
            }
        }
    }
}
