import QtQuick 2.11
import QtQuick.Controls 2.4

Control {
    id: control
    width: 80
    height: 30

    property alias mouse_area: mouse_area
    property alias text: text.text

    onHoveredChanged: anim.start()

    Rectangle {
        anchors.fill: parent
        border.width: 1
        border.color: control.hovered ? "#ff0000" : "#black"
        radius: 2
        color: control.hovered ? "#00ff00" : "white"
        Text {
            id: text
            anchors.centerIn: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            height: parent.height
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
        SequentialAnimation {
            id: anim
            ScaleAnimator {
                target: control
                from: 1
                to: 1.1
                duration: 250
            }
            ScaleAnimator {
                target: control
                from: 1.1
                to: 1
                duration: 250
            }
        }
    }
}











