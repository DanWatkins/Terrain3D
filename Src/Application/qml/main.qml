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

    Button {
        id: button_settings
        text: "Settings"

        anchors.top:  parent.top
        anchors.left: parent.left
        anchors.margins: 10

        width: 70
        height: 35

        onClicked: {
            settingsPane.source = "SettingsPane.qml"
        }
    }

    Button {
        id: button_reload
        text: "Reload"

        anchors.top:  button_settings.bottom
        anchors.left: parent.left
        anchors.margins: 10

        width: 70
        height: 35
    }
}
