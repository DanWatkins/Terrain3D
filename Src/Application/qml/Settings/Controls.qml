import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2


Item {
    function loadSettings() {
        console.log("Loading for controls pane");
    }

    function saveSettings() {
        console.log("Saving for controls pane");
    }

    Text {
        anchors.centerIn: parent
        text: qsTr("Not implemented yet...")
    }
}
