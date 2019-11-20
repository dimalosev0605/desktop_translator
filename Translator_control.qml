import QtQuick 2.11
import QtQuick.Controls 2.4

Control {
    id: control

    property alias text: text.text
    property alias mouse_area: mouse_area
    property alias color: rect.color

    onHoveredChanged: anim.start()

    width: 50
    height: user_input_field.height

    Rectangle {
        id: rect
        anchors.fill: parent
        border.width: 1
        border.color: "black"
        radius: 2
        Text {
            id: text
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




























