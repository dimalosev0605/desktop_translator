import QtQuick 2.11
import QtQuick.Controls 2.4

Control {
    id: control

    property alias mouse_area: mouse_area

    Rectangle {
        anchors.fill: parent
        color: control.hovered ? "#ff0000" : "white"
        Image {
            anchors.fill: parent
//            source: ""
        }
        MouseArea {
            id: mouse_area
            anchors.fill: parent
        }
    }
}
