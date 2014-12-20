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
        SaveLoad.cbRead(Settings.WorldTerrainBlockSize,comboBox_terrainBlockSize);
        SaveLoad.valueRead(Settings.WorldTerrainHeightScale, spinBox_terrainHeightScale);
        SaveLoad.valueRead(Settings.WorldTerrainSpacing, spinBox_terrainSpacing);
        SaveLoad.cbRead(Settings.WorldTerrainSpanSize,comboBox_terrainSpanSize);
    }

    function saveSettings() {
        SaveLoad.valueSave(Settings.WorldGeneratorSeed, spinBox_generatorSeed);
        SaveLoad.valueSave(Settings.WorldGeneratorFaultCount, spinBox_faultCount);
        SaveLoad.cbSave(Settings.WorldGeneratorSize, comboBox_worldGeneratorSize);
        SaveLoad.cbSave(Settings.WorldGeneratorTextureMapResolution, comboBox_generatorTextureMapResolution);
        SaveLoad.cbSave(Settings.WorldTerrainBlockSize, comboBox_terrainBlockSize);
        SaveLoad.valueSave(Settings.WorldTerrainHeightScale, spinBox_terrainHeightScale);
        SaveLoad.valueSave(Settings.WorldTerrainSpacing, spinBox_terrainSpacing);
        SaveLoad.cbSave(Settings.WorldTerrainSpanSize, comboBox_terrainSpanSize);
    }

    width: 600
    height: 400

    GroupBox {
        id: groupBox1
        x: 8
        y: 8
        width: 265
        height: 125
        title: qsTr("Generator")


        ComboBox {
            id: comboBox_worldGeneratorSize
            x: 125
            y: 1
            width: 125
            height: 20
            model: [64, 128, 256, 512, 1024, 2048, 4096, 8192]
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
        }

        Label {
            id: label2
            x: 1
            y: 31
            text: qsTr("Texture Map Resolution:")
        }

        Label {
            id: label3
            x: 91
            y: 83
            text: qsTr("Seed:")
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
            width: 125
            height: 20
        }

        Label {
            id: label4
            x: 19
            y: 4
            text: qsTr("Spacing:")
        }

        SpinBox {
            id: spinBox_terrainHeightScale
            x: 66
            y: 26
            width: 125
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
            x: 10
            y: 57
            text: qsTr("Block Size:")
        }

        ComboBox {
            id: comboBox_terrainBlockSize
            x: 66
            y: 53
            width: 125
            height: 20
            model: [4, 8, 16, 32, 64]
        }

        ComboBox {
            id: comboBox_terrainSpanSize
            x: 66
            y: 80
            width: 125
            height: 20
            model: [8, 16, 32, 64, 128, 256, 512, 1024]
        }

        Label {
            id: label7
            x: 10
            y: 84
            text: qsTr("Span Size:")
        }
    }
}
