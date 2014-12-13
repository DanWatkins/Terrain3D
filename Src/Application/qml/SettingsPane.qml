import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D.Settings 1.0

Item {
    Rectangle {
        anchors.fill: parent

        opacity: 0.45
        color: "blue"

        border.width: 2
        border.color: "black"
    }



    GroupBox {
        title: "Graphics"

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5

        ColumnLayout {
            anchors.fill: parent

            CheckBox {
                id: wireframe
                text: "Wireframe"
                Layout.fillWidth: true

                checked: MySettings.value(MySettings.KeyWireframe)
                onCheckedChanged: {
                    MySettings.setValue(MySettings.KeyWireframe,
                                        wireframe.checked)
                }
            }

            RowLayout {
                Layout.fillWidth: true

                Slider {
                    Layout.fillWidth: true
                }
                Text {
                    text: "LOD"
                }
            }
        }
    }
}
