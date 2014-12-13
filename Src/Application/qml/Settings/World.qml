import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

Item {
    width: 600
    height: 400

    GroupBox {
        id: groupBox1
        x: 8
        y: 8
        width: 265
        height: 257
        title: qsTr("Generator")

        Label {
            id: label1
            x: 95
            y: 5
            text: qsTr("Size:")
        }

        ComboBox {
            id: comboBox1
            x: 124
            y: 1
        }

        ComboBox {
            id: comboBox2
            x: 124
            y: 27
        }

        Label {
            id: label2
            x: 0
            y: 31
            text: qsTr("Texture Map Resolution:")
        }

        Label {
            id: label3
            x: 90
            y: 57
            text: qsTr("Seed:")
        }

        SpinBox {
            id: spinBox1
            x: 124
            y: 54
            width: 125
            height: 20
            maximumValue: 9999999
        }
    }

    GroupBox {
        id: groupBox2
        x: 279
        y: 8
        width: 313
        height: 257
        title: qsTr("Terrain")

        SpinBox {
            id: spinBox2
            x: 66
            y: 0
            width: 80
            height: 20
        }

        Label {
            id: label4
            x: 13
            y: 4
            text: qsTr("Spacing:")
        }

        SpinBox {
            id: spinBox3
            x: 66
            y: 26
            width: 80
            height: 20
        }

        Label {
            id: label5
            x: -3
            y: 30
            text: qsTr("Height Scale:")
        }

        Label {
            id: label6
            x: 6
            y: 56
            text: qsTr("Block Size:")
        }

        ComboBox {
            id: comboBox3
            x: 58
            y: 53
            width: 88
            height: 20
        }

        ComboBox {
            id: comboBox4
            x: 58
            y: 79
            width: 88
            height: 20
        }

        Label {
            id: label7
            x: 6
            y: 83
            text: qsTr("Span Size:")
        }
    }
}
