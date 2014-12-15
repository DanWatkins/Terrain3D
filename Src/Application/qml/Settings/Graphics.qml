import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0

Item {
    function loadSettings() {
       console.log("Loading for graphics pane");
    }

    function saveSettings() {
        console.log("Saving for graphics pane");

        appSettings.enqueueValue(Settings.GraphicsScreenResolutionWidth, spinBox_screenSizeWidth.value);
        appSettings.enqueueValue(Settings.GraphicsScreenResolutionHeight, spinBox_screenSizeHeight.value);
        appSettings.enqueueValue(Settings.GraphicsScreenIsFullscreen, checkBox_screenIsFullscreen.value);
        appSettings.enqueueValue(Settings.GraphicsCameraFOV, slider_cameraFOV.value);
        appSettings.enqueueValue(Settings.GraphicsCameraLOD, slider_cameraLOD.value);
        appSettings.enqueueValue(Settings.GraphicsCameraPositionX, spinBox_cameraPositionX.value);
        appSettings.enqueueValue(Settings.GraphicsCameraPositionX, spinBox_cameraPositionY.value);
        appSettings.enqueueValue(Settings.GraphicsCameraPositionX, spinBox_cameraPositionZ.value);
        appSettings.enqueueValue(Settings.GraphicsCameraWireframe, checkBox_cameraWireframe.value);
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
            width: 252
            height: 22
            tickmarksEnabled: true
        }

        Slider {
            id: slider_cameraLOD
            x: 47
            y: 61
            width: 252
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
    }
}
