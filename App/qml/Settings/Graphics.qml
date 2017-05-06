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
    title: "Graphics"

    SettingSpinBox {
        title: "Screen Width"
        settingsKey: Settings.GraphicsScreenResolutionWidth

        minimumValue: 640
        maximumValue: 10000
    }

    SettingSpinBox {
        title: "Screen Height"
        settingsKey: Settings.GraphicsScreenResolutionHeight

        minimumValue: 480
        maximumValue: 10000
    }

    SettingCheckBox {
        title: "Fullscreen"
        settingsKey: Settings.GraphicsScreenIsFullscreen
    }

    SettingSpinBox {
        title: "Camera Pos.x"
        settingsKey: Settings.GraphicsCameraPositionX

        minimumValue: -10000
        maximumValue: 10000
    }

    SettingSpinBox {
        title: "Camera Pos.y"
        settingsKey: Settings.GraphicsCameraPositionY

        minimumValue: -10000
        maximumValue: 10000
    }

    SettingSpinBox {
        title: "Camera Pos.z"
        settingsKey: Settings.GraphicsCameraPositionZ

        minimumValue: -10000
        maximumValue: 10000
    }

    SettingSlider {
        title: "Camera FOV"
        settingsKey: Settings.GraphicsCameraFOV

        minimumValue: 0
        maximumValue: 3
        stepSize: 0.1
    }

    SettingSlider {
        title: "Camera LOD Factor"
        settingsKey: Settings.GraphicsCameraLODFactor

        minimumValue: 0.1
        maximumValue: 1.0
        stepSize: 0.05
    }

    SettingSlider {
        id: slider_graphicsCameraLODNear
        title: "Camera LOD Near"
        settingsKey: Settings.GraphicsCameraLODNear

        minimumValue: 0.0
        maximumValue: 1000.0
        stepSize: 0.05
    }

    SettingSlider {
        id: slider_graphicsCameraLODFar
        title: "Camera LOD Far"
        settingsKey: Settings.GraphicsCameraLODFar

        minimumValue: 0.0
        maximumValue: 1000
        stepSize: 50
    }
}
