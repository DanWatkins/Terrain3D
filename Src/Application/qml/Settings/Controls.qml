import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2


Item {
    function loadSettings() {
    }

    function saveSettings() {
    }


    ScrollView {
       anchors.fill: parent
       anchors.margins: 5

       GroupBox {
           x: 0
           y: 0
           width: 200
           height: 500

           title: "Terrain"

           Slider {
               x: 10
               y: 10
               width: 180
               height: 30
           }
       }
    }
}
