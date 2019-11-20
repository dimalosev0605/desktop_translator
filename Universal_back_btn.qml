import QtQuick 2.11
import QtQuick.Controls 2.4

Control {
    id: control
    width: 30
    height: 30

    Rectangle {
        anchors.fill: parent
        color: control.hovered ? "#00ff00" : "white"
        Image {
            id: img
            anchors.fill: parent
            source: "back_btn_icon.svg"
        }
        MouseArea {
            id: mouse_area
            anchors.fill: parent
            onClicked: stack_view.pop()
        }
    }
}






















