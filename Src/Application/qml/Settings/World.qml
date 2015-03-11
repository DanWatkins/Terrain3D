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
        x: 8
        y: 8
        width: 264
        height: 278
        title: qsTr("Terrain")


        ComboBox {
            id: comboBox_worldGeneratorSize
            x: 130
            y: 0
            width: 120
            height: 20
            model: [32, 64, 128, 256, 512, 1024, 2048, 4096, 8192]
        }

        ComboBox {
            id: comboBox_generatorTextureMapResolution
            x: 130
            y: 80
            width: 120
            height: 20
            model: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        }

        SpinBox {
            id: spinBox_generatorSeed
            x: 130
            y: 169
            width: 120
            height: 20
            maximumValue: 9999999
        }

        Label {
            id: label1
            x: 101
            y: 4
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

        SpinBox {
            id: spinBox_faultCount
            x: 130
            y: 138
            width: 120
            height: 20
            maximumValue: 100000
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

        Slider {
            id: slider_generatorSmoothIntensity
            x: 130
            y: 195
            width: 90
            height: 22
            stepSize: 0.01
            value: 0.65
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
            id: label_genSmoothIntensity
            x: 226
            y: 199
            width: 25
            height: 15
            text: slider_generatorSmoothIntensity.value
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
            id: label10
            x: 226
            y: 227
            width: 25
            height: 15
            text: slider_terrainLightIntensity.value
        }

        Slider {
            id: slider_terrainLightIntensity
            x: 130
            y: 223
            width: 90
            height: 22
            stepSize: 1
            maximumValue: 50
            value: 12.0
        }

        ComboBox {
            id: comboBox_terrainChunkSize
            x: 130
            y: 26
            width: 120
            height: 20
            model: [4, 8, 16, 32, 64, 128, 256]
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

        ComboBox {
            id: comboBox_terrainSpanSize
            x: 130
            y: 52
            width: 120
            height: 20
            model: [8, 16, 32, 64, 128, 256, 512, 1024]
        }

        Label {
            id: label5
            x: 61
            y: 111
            text: qsTr("Height Scale:")
        }

        SpinBox {
            id: spinBox_terrainHeightScale
            x: 130
            y: 107
            width: 120
            height: 20
        }






    }
}
