import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0
import "SaveLoad.js" as SaveLoad

Item {
    id: item1
    function loadSettings() {
        SaveLoad.valueRead(Settings.WorldGeneratorSeed, spinBox_generatorSeed);
        SaveLoad.valueRead(Settings.WorldGeneratorFaultCount, spinBox_faultCount);
        SaveLoad.cbRead(Settings.WorldGeneratorSize, comboBox_worldGeneratorSize);
        SaveLoad.cbRead(Settings.WorldGeneratorTextureMapResolution,comboBox_generatorTextureMapResolution);
        SaveLoad.cbRead(Settings.WorldTerrainChunkSize,comboBox_terrainChunkSize);
        SaveLoad.valueRead(Settings.WorldTerrainHeightScale, spinBox_terrainHeightScale);
        SaveLoad.cbRead(Settings.WorldTerrainSpanSize,comboBox_terrainSpanSize);
        SaveLoad.valueRead(Settings.WorldTerrainLightIntensity, slider_terrainLightIntensity);
        SaveLoad.valueRead(Settings.WorldGeneratorSmoothing, slider_generatorSmoothIntensity);
    }

    function saveSettings() {
        SaveLoad.valueSave(Settings.WorldGeneratorSeed, spinBox_generatorSeed);
        SaveLoad.valueSave(Settings.WorldGeneratorFaultCount, spinBox_faultCount);
        SaveLoad.cbSave(Settings.WorldGeneratorSize, comboBox_worldGeneratorSize);
        SaveLoad.cbSave(Settings.WorldGeneratorTextureMapResolution, comboBox_generatorTextureMapResolution);
        SaveLoad.cbSave(Settings.WorldTerrainChunkSize, comboBox_terrainChunkSize);
        SaveLoad.valueSave(Settings.WorldTerrainHeightScale, spinBox_terrainHeightScale);
        SaveLoad.cbSave(Settings.WorldTerrainSpanSize, comboBox_terrainSpanSize);
        SaveLoad.valueSave(Settings.WorldTerrainLightIntensity, slider_terrainLightIntensity);
        SaveLoad.valueSave(Settings.WorldGeneratorSmoothing, slider_generatorSmoothIntensity);
    }

    width: 500
    height: 290

    GroupBox {
        id: groupBox1
        width: parent.width
        height: parent.height
        title: qsTr("Terrain")


        Label {
            id: label1
            x: 101
            y: 4
            width: 23
            height: 5
            text: qsTr("Size:")
            horizontalAlignment: Text.AlignRight
        }

        Label {
            id: label2
            x: 6
            y: 84
            text: qsTr("Texture Map Resolution:")
            horizontalAlignment: Text.AlignRight
        }

        Label {
            id: label3
            x: 96
            y: 173
            text: qsTr("Seed:")
            horizontalAlignment: Text.AlignRight
        }

        Label {
            id: label8
            x: 66
            y: 142
            width: 58
            height: 13
            text: qsTr("Fault Count:")
            horizontalAlignment: Text.AlignRight
        }

        Label {
            id: label9
            x: 18
            y: 200
            width: 106
            height: 13
            text: qsTr("Smooth Intensity:")
            horizontalAlignment: Text.AlignRight
        }

        Label {
            id: label11
            x: 40
            y: 228
            width: 84
            height: 13
            text: qsTr("Light Intensity:")
            horizontalAlignment: Text.AlignRight
        }

        Label {
            id: label6
            x: 68
            y: 30
            text: qsTr("Chunk Size:")
        }

        Label {
            id: label7
            x: 74
            y: 56
            text: qsTr("Span Size:")
        }

        Label {
            id: label5
            x: 61
            y: 111
            text: qsTr("Height Scale:")
        }

        Column {
            id: item2
            anchors.left: parent.left
            anchors.leftMargin: 130
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            spacing: 5

            ComboBox {
                id: comboBox_terrainSpanSize
                x: 5
                Layout.fillWidth: parent
                height: 20
                model: [8, 16, 32, 64, 128, 256, 512, 1024]
            }

            ComboBox {
                id: comboBox_terrainChunkSize
                x: 5
                Layout.fillWidth: parent
                height: 20
                model: [4, 8, 16, 32, 64, 128, 256]
            }

            ComboBox {
                id: comboBox_generatorTextureMapResolution
                x: 5
                Layout.fillWidth: parent
                height: 20
                model: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
            }

            ComboBox {
                id: comboBox_worldGeneratorSize
                x: 5
                Layout.fillWidth: parent
                height: 20
                model: [32, 64, 128, 256, 512, 1024, 2048, 4096, 8192]
            }

            SpinBox {
                id: spinBox_terrainHeightScale
                x: 5
                Layout.fillWidth: parent
                height: 20
            }

            SpinBox {
                id: spinBox_faultCount
                x: 5
                Layout.fillWidth: parent
                height: 20
                maximumValue: 100000
            }

            SpinBox {
                id: spinBox_generatorSeed
                x: 5
                Layout.fillWidth: parent
                height: 20
                maximumValue: 9999999
            }

            Slider {
                id: slider_terrainLightIntensity
                width: 90
                height: 22
                stepSize: 1
                maximumValue: 50
                value: 12.0
            }

            Slider {
                id: slider_generatorSmoothIntensity
                        width: 90
                        height: 22
                        stepSize: 0.01
                        value: 0.65
            }
        }
    }
}
