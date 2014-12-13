import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0
import Terrain3D.Settings 1.0

Terrain3DWindow {
    Camera {
        id: mainCamera
        y: 40
        objectName: "t3d_mainCamera"
        anchors.fill: parent
        anchors.margins: 0
    }

    SettingsPane {
        anchors.fill: parent
    }
}
