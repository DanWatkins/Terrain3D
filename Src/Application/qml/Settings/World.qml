import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0
import "SaveLoad.js" as SaveLoad

Item {
    function loadSettings() {
        SaveLoad.valueRead(Settings.WorldGeneratorSeed, spinBox_generatorSeed);
        SaveLoad.valueRead(Settings.WorldGeneratorFaultCount, spinBox_faultCount);
        SaveLoad.cbRead(Settings.WorldGeneratorSize, comboBox_worldGeneratorSize);
        SaveLoad.cbRead(Settings.WorldGeneratorTextureMapResolution,comboBox_generatorTextureMapResolution);
        SaveLoad.cbRead(Settings.WorldTerrainChunkSize,comboBox_terrainChunkSize);
        SaveLoad.valueRead(Settings.WorldTerrainHeightScale, spinBox_terrainHeightScale);
        SaveLoad.valueRead(Settings.WorldTerrainSpacing, spinBox_terrainSpacing);
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
        SaveLoad.valueSave(Settings.WorldTerrainSpacing, spinBox_terrainSpacing);
        SaveLoad.cbSave(Settings.WorldTerrainSpanSize, comboBox_terrainSpanSize);
        SaveLoad.valueSave(Settings.WorldTerrainLightIntensity, slider_terrainLightIntensity);
        SaveLoad.valueSave(Settings.WorldGeneratorSmoothing, slider_generatorSmoothIntensity);
    }

    width: 500
    height: 166

    GroupBox {
        id: groupBox1
        x: 8
        y: 8
        width: 265
        height: 152
        title: qsTr("Generator")


        ComboBox {
            id: comboBox_worldGeneratorSize
            x: 125
            y: 1
            width: 125
            height: 20
            model: [32, 64, 128, 256, 512, 1024, 2048, 4096, 8192]
        }

        ComboBox {
            id: comboBox_generatorTextureMapResolution
            x: 125
            y: 27
            width: 125
            height: 20
            model: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        }

        SpinBox {
            id: spinBox_generatorSeed
            x: 125
            y: 79
            width: 125
            height: 20
            maximumValue: 9999999
        }

        Label {
            id: label1
            x: 96
            y: 5
            text: qsTr("Size:")
            horizontalAlignment: Text.AlignRight
        }

        Label {
            id: label2
            x: 1
            y: 31
            text: qsTr("Texture Map Resolution:")
            horizontalAlignment: Text.AlignRight
        }

        Label {
            id: label3
            x: 91
            y: 83
            text: qsTr("Seed:")
            horizontalAlignment: Text.AlignRight
        }

        SpinBox {
            id: spinBox_faultCount
            x: 125
            y: 53
            width: 125
            height: 20
            maximumValue: 100000
        }

        Label {
            id: label8
            x: 61
            y: 57
            width: 58
            height: 13
            text: qsTr("Fault Count:")
            horizontalAlignment: Text.AlignRight
        }

        Slider {
            id: slider_generatorSmoothIntensity
            x: 126
            y: 105
            width: 83
            height: 22
            stepSize: 0.01
            value: 0.65
        }

        Label {
            id: label9
            x: 14
            y: 110
            width: 106
            height: 13
            text: qsTr("Smooth Intensity")
            horizontalAlignment: Text.AlignRight
        }

        Label {
            id: label_genSmoothIntensity
            x: 222
            y: 110
            width: 27
            height: 13
            text: slider_generatorSmoothIntensity.value
        }

    }

    GroupBox {
        id: groupBox2
        x: 279
        y: 8
        width: 221
        height: 152
        title: qsTr("Terrain")

        SpinBox {
            id: spinBox_terrainSpacing
            x: 79
            y: 0
            width: 125
            height: 20
        }

        Label {
            id: label4
            x: 32
            y: 4
            text: qsTr("Spacing:")
        }

        SpinBox {
            id: spinBox_terrainHeightScale
            x: 79
            y: 26
            width: 125
            height: 20
        }

        Label {
            id: label5
            x: 10
            y: 30
            text: qsTr("Height Scale:")
        }

        Label {
            id: label6
            x: 23
            y: 57
            text: qsTr("Chunk Size:")
        }

        ComboBox {
            id: comboBox_terrainChunkSize
            x: 79
            y: 53
            width: 125
            height: 20
            model: [4, 8, 16, 32, 64, 128, 256]
        }

        ComboBox {
            id: comboBox_terrainSpanSize
            x: 79
            y: 80
            width: 125
            height: 20
            model: [8, 16, 32, 64, 128, 256, 512, 1024]
        }

        Label {
            id: label7
            x: 23
            y: 84
            text: qsTr("Span Size:")
        }

        Slider {
            id: slider_terrainLightIntensity
            x: 79
            y: 107
            width: 83
            height: 22
            stepSize: 1
            maximumValue: 50
            value: 12.0
        }

        Label {
            id: label10
            x: 168
            y: 112
            width: 36
            height: 13
            text: slider_terrainLightIntensity.value
        }

        Label {
            id: label11
            x: 23
            y: 112
            width: 50
            height: 13
            text: qsTr("Light Intensity:")
            horizontalAlignment: Text.AlignRight
        }
    }
}
