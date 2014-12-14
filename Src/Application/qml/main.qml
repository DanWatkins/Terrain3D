import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0
import "SettingsPaneCreation.js" as CreationScript

Terrain3DWindow {
    id: appWindow

    Camera {
        id: mainCamera
        y: 40
        objectName: "t3d_mainCamera"
        anchors.fill: parent
        anchors.margins: 0
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
            var cmp = CreationScript.createComponent("SettingsPane.qml",
                                                     appWindow,
                                                     {"anchors.fill": appWindow});
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

    /*SettingsPane {
        anchors.fill: appWindow
    }*/
}
