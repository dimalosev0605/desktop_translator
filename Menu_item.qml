import QtQuick 2.11
import QtQuick.Controls 2.4

Control {
    id: control

    property alias text: text.text
    property alias img: img
    property alias mouse_area: mouse_area

    width: file_menu.width
    height: 30

    Rectangle {
        anchors.fill: parent
        color: control.hovered ? "#00ff00" : "white"
        Image {
            id: img
            width: 30
            height: 30
        }
        Text {
            id: text
            anchors.left: img.right
            anchors.top: img.top
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            width: control.width - img.width
            height: control.height
            fontSizeMode: Text.Fit
            minimumPointSize: 5
            font.pointSize: 10
            elide: Text.ElideRight
            wrapMode: Text.WordWrap
        }
        MouseArea {
            id: mouse_area
            anchors.fill: parent
        }
    }

}












