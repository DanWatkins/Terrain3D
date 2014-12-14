import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

Item {
    function saveAllSettings()
    {
        console.log("Saving for world pane");
        Settings.enqueueValue(Settings.KeyShowHud, false);
        Settings.enqueueValue(Settings.KeyWireframe, true);
    }

    width: 600
    height: 400

    GroupBox {
        id: groupBox1
        x: 8
        y: 8
        width: 265
        height: 257
        title: qsTr("Generator")


        ComboBox {
            id: comboBox_worldGeneratorSize
            x: 125
            y: 1
        }

        ComboBox {
            id: comboBox_generatorTextureMapResolution
            x: 125
            y: 27
        }

        SpinBox {
            id: spinBox_generatorSeed
            x: 124
            y: 54
            width: 125
            height: 20
            maximumValue: 9999999
        }

        Label {
            id: label1
            x: 95
            y: 5
            text: qsTr("Size:")
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

    }

    GroupBox {
        id: groupBox2
        x: 279
        y: 8
        width: 313
        height: 257
        title: qsTr("Terrain")

        SpinBox {
            id: spinBox_terrainSpacing
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
            id: spinBox_terrainHeightScale
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
            id: comboBox_terrainBlockSize
            x: 58
            y: 53
            width: 88
            height: 20
        }

        ComboBox {
            id: comboBox_terrainSpanSize
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
