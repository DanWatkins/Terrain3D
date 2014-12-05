import QtQuick 2.0
import QtQuick.Controls 1.2
import Terrain3DX 1.0

Item {
    width: 800
    height: 600

    Camera {
        id: renderer
        anchors.fill: parent
        anchors.margins: 0
    }
}
