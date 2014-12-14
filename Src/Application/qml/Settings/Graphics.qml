import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

Item {
    function saveAllSettings()
    {
        console.log("Saving for graphics pane");
    }


    width: 600
    height: 400
    GroupBox {
        x: 8
        y: 8
        width: 196
        height: 66
        title: "Screen"

        Label {
            id: label1
            x: 0
            y: 4
            text: qsTr("Resolution:")
        }

        SpinBox {
            id: spinBox1
            x: 60
            y: 0
            width: 58
            height: 20
            value: 800
            maximumValue: 10000
        }

        SpinBox {
            id: spinBox2
            x: 124
            y: 0
            width: 58
            height: 20
            value: 600
            maximumValue: 10000
        }

        CheckBox {
            id: checkBox1
            x: 0
            y: 26
            text: qsTr("Fullscreen")
        }
    }

    GroupBox {
        id: groupBox1
        x: 210
        y: 8
        width: 325
        height: 300
        title: qsTr("Camera")

        SpinBox {
            id: spinBox3
            x: 47
            y: 0
            height: 20
            decimals: 3
            maximumValue: 100000
        }

        SpinBox {
            id: spinBox4
            x: 133
            y: 0
            height: 20
            decimals: 3
            maximumValue: 100000
        }

        SpinBox {
            id: spinBox5
            x: 219
            y: 0
            height: 20
            decimals: 3
            maximumValue: 100000
        }

        Slider {
            id: sliderHorizontal1
            x: 47
            y: 33
            width: 252
            height: 22
            tickmarksEnabled: true
        }

        Slider {
            id: sliderHorizontal2
            x: 47
            y: 61
            width: 252
            height: 22
            tickmarksEnabled: true
        }

        CheckBox {
            id: checkBox2
            x: 47
            y: 89
            text: qsTr("Render wireframe")
        }

        ////////// LABELS
        Label {
            id: label2
            x: 0
            y: 4
            text: qsTr("Position:")
        }

        Label {
            id: label3
            x: 8
            y: 38
            text: qsTr("FOV:")
        }

        Label {
            id: label4
            x: 8
            y: 66
            text: qsTr("LOD:")
        }
    }
}
