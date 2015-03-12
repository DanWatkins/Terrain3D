import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0

Item {
    id: root

    width: 200
    height: 30

    property int settingsKey: 0
    property string title: "";

    function load() {
        checkBox.checked = appSettings.value(settingsKey);
    }

    function save() {
        appSettings.enqueueValue(settingsKey, checkBox.checked);
        appSettings.applyQueuedValues();
    }

    CheckBox {
        id: checkBox
        text: title
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 8

        onClicked: {
            root.save();
        }

    }

    Component.onCompleted: {
        load();
    }
}
