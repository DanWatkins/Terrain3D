//==================================================================================================================|
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0

import "../Controls/"

SettingGroupBox {
    title: "World"

    SettingComboBox {
        title: "Size"
        settingsKey: Settings.WorldGeneratorSize
        model: [32, 64, 128, 256, 512, 1024, 2048, 4096, 8192]
    }

    SettingComboBox {
        title: "Texture Map Resolution"
        settingsKey: Settings.WorldGeneratorTextureMapResolution
        model: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    }

    SettingComboBox {
        title: "Chunk Size"
        settingsKey: Settings.WorldTerrainChunkSize
        model: [8, 16, 32, 64, 128, 256, 512, 1024]
    }

    SettingComboBox {
        title: "Span Size"
        settingsKey: Settings.WorldTerrainSpanSize
        model: [8, 16, 32, 64, 128, 256, 512, 1024]
    }

    SettingSpinBox {
        title: "Seed"
        settingsKey: Settings.WorldGeneratorSeed
        minimumValue: 0
        maximumValue: 2000000000;
        stepSize: 1
    }

    SettingSpinBox {
        title: "Fault Count"
        settingsKey: Settings.WorldGeneratorFaultCount
        minimumValue: 0
        maximumValue: 10000
        stepSize: 10
    }

    SettingSpinBox {
        title: "Height Scale"
        settingsKey: Settings.WorldTerrainHeightScale
        minimumValue: 0
        maximumValue: 1000
        stepSize: 1
    }

    SettingSlider {
        title: "Smoothing"
        settingsKey: Settings.WorldGeneratorSmoothing
        minimumValue: 0
        maximumValue: 1
        stepSize: 0.05
    }

    SettingSlider {
        title: "Light Intensity"
        settingsKey: Settings.WorldTerrainLightIntensity
        minimumValue: 1
        maximumValue: 50
        stepSize: 1
    }
}
