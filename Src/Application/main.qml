import QtQuick 2.0
import QtQuick.Controls 1.2
import Terrain3D 1.0

Item {
    width: 800
    height: 600

    Camera {
        id: mainCamera
        objectName: "t3d_mainCamera"
        anchors.fill: parent
        anchors.margins: 0
    }
}
