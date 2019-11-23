import QtQuick 2.11
import QtQuick.Controls 2.4

Rectangle {
    id: root
    width: blocks_scroll_view_frame.width
    height: blocks_scroll_view_frame.height / 2
    border.width: 1
    border.color: activeFocus ? "#00ff00" : "black"

    property alias transcription: transcription.text
    property alias type_speech: type_speech.text
    property alias syns: syns.text
    property alias means: means.text
    property alias examples: examples.text

    property int left_margin: 2
    property int top_margin: 2
    property int text_height: 20
    Text {
        id: transcription
        anchors.left: root.left
        anchors.leftMargin: left_margin
        anchors.top: root.top
        anchors.topMargin: top_margin
        color: "gray"
        fontSizeMode: Text.Fit
        minimumPointSize: 5
        font.pointSize: 10
        height: text_height
    }
    Text {
        id: type_speech
        anchors.left: transcription.right
        anchors.leftMargin: left_margin
        anchors.top: transcription.top
        color: "green"
        fontSizeMode: Text.Fit
        minimumPointSize: 5
        font.pointSize: 10
        height: text_height
    }
    Text {
        id: syns
        anchors.top: transcription.bottom
        anchors.topMargin: top_margin
        anchors.left: transcription.left
        color: "blue"
        height: text_height
        verticalAlignment: Text.AlignLeft
        horizontalAlignment: Text.AlignLeft
        width: root.width
        fontSizeMode: Text.Fit
        minimumPointSize: 5
        font.pointSize: 10
        elide: Text.ElideRight
        wrapMode: Text.WordWrap
    }
    Text {
        id: means
        anchors.top: syns.bottom
        anchors.topMargin: top_margin
        anchors.left: syns.left
        color: "red"
        fontSizeMode: Text.Fit
        height: text_height
        verticalAlignment: Text.AlignLeft
        horizontalAlignment: Text.AlignLeft
        width: root.width
        minimumPointSize: 5
        font.pointSize: 10
        elide: Text.ElideRight
        wrapMode: Text.WordWrap
    }
    Text {
        id: examples
        anchors.top: means.bottom
        anchors.topMargin: top_margin
        anchors.left: means.left
        anchors.bottom: root.bottom
        color: "gray"
        verticalAlignment: Text.AlignLeft
        horizontalAlignment: Text.AlignLeft
        width: root.width
        fontSizeMode: Text.Fit
        minimumPointSize: 5
        font.pointSize: 10
        elide: Text.ElideRight
        wrapMode: Text.WordWrap
    }
    Text {
        id: idx
        anchors.right: root.right
        anchors.rightMargin: 1
        anchors.bottom: root.bottom
        anchors.bottomMargin: 1
        text: index + 1
        minimumPointSize: 3
        font.pointSize: 10
        fontSizeMode: Text.Fit
    }
}









