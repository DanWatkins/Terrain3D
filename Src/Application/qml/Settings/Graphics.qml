import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0
import "SaveLoad.js" as SaveLoad

Item {
    function loadSettings() {
        SaveLoad.valueRead(Settings.GraphicsScreenResolutionWidth, spinBox_screenSizeWidth);
        SaveLoad.valueRead(Settings.GraphicsScreenResolutionHeight, spinBox_screenSizeHeight);
        SaveLoad.checkedRead(Settings.GraphicsScreenIsFullscreen, checkBox_screenIsFullscreen);

        SaveLoad.valueRead(Settings.GraphicsCameraFOV, slider_cameraFOV);
        SaveLoad.valueRead(Settings.GraphicsCameraLOD, slider_cameraLOD);
        SaveLoad.valueRead(Settings.GraphicsCameraPositionX,spinBox_cameraPositionX);
        SaveLoad.valueRead(Settings.GraphicsCameraPositionY,spinBox_cameraPositionY);
        SaveLoad.valueRead(Settings.GraphicsCameraPositionZ,spinBox_cameraPositionZ);
        SaveLoad.checkedRead(Settings.GraphicsCameraWireframe, checkBox_cameraWireframe);
    }

    function saveSettings() {
        SaveLoad.valueSave(Settings.GraphicsScreenResolutionWidth, spinBox_screenSizeWidth);
        SaveLoad.valueSave(Settings.GraphicsScreenResolutionHeight, spinBox_screenSizeHeight);
        SaveLoad.checkedSave(Settings.GraphicsScreenIsFullscreen, checkBox_screenIsFullscreen);

        SaveLoad.valueSave(Settings.GraphicsCameraFOV, slider_cameraFOV);
        SaveLoad.valueSave(Settings.GraphicsCameraLOD, slider_cameraLOD);
        SaveLoad.valueSave(Settings.GraphicsCameraPositionX, spinBox_cameraPositionX);
        SaveLoad.valueSave(Settings.GraphicsCameraPositionY, spinBox_cameraPositionY);
        SaveLoad.valueSave(Settings.GraphicsCameraPositionZ, spinBox_cameraPositionZ);
        SaveLoad.checkedSave(Settings.GraphicsCameraWireframe, checkBox_cameraWireframe);
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
            id: spinBox_screenSizeWidth
            x: 60
            y: 0
            width: 58
            height: 20
            value: 800
            maximumValue: 10000
        }

        SpinBox {
            id: spinBox_screenSizeHeight
            x: 124
            y: 0
            width: 58
            height: 20
            value: 600
            maximumValue: 10000
        }

        CheckBox {
            id: checkBox_screenIsFullscreen
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
            id: spinBox_cameraPositionX
            x: 47
            y: 0
            height: 20
            decimals: 3
            maximumValue: 100000
        }

        SpinBox {
            id: spinBox_cameraPositionY
            x: 133
            y: 0
            height: 20
            decimals: 3
            maximumValue: 100000
        }

        SpinBox {
            id: spinBox_cameraPositionZ
            x: 219
            y: 0
            height: 20
            decimals: 3
            maximumValue: 100000
        }

        Slider {
            id: slider_cameraFOV
            x: 47
            y: 33
            width: 215
            height: 22
            maximumValue: 180
            tickmarksEnabled: true
        }

        Slider {
            id: slider_cameraLOD
            x: 47
            y: 61
            width: 215
            height: 22
            tickmarksEnabled: true
        }

        CheckBox {
            id: checkBox_cameraWireframe
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

        Label {
            id: label_fovValue
            x: 268
            y: 42
            width: 41
            height: 13
            text: slider_cameraFOV.value
        }

        Label {
            id: label_lodValue
            x: 268
            y: 66
            width: 41
            height: 13
            text: slider_cameraLOD.value
        }
    }
}
