import QtQuick 2.11
import QtQuick.Controls 2.4

Rectangle {
    id: root
    width: words_scroll_view_frame.width
    height: 50
    border.width: 1
    border.color: activeFocus ? "#00ff00" : "black"

    property alias word_and_transcription: word_and_transcripton.text
    property alias means: means.text
    property alias syns: syns.text
    property alias date: date.text

    Row  {
        Rectangle {
            border.width: 1
            border.color: "black"
            height: root.height
            width: 30
            color: m_area.containsMouse ? "#ff0000" : "white"
            Text {
                id: idx
                text: index + 1
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
                id: m_area
                anchors.fill: parent
                onClicked: {
                    words_data_model.remove_word(index)
                    user_input_field.text = words_data_model.word_get_word()
                    means_field.text = words_data_model.word_get_means()
                    translations_filed.text = words_data_model.word_get_syns()
                }
            }
        }
        Rectangle {
            border.width: 1
            border.color: "black"
            height: root.height
            width: (root.width - idx.width)/ 4
            Text {
                id: word_and_transcripton
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
        }
        Rectangle {
            border.width: 1
            border.color: "black"
            height: root.height
            width: (root.width - idx.width)/ 4
            Text {
                id: means
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
        }
        Rectangle {
            border.width: 1
            border.color: "black"
            height: root.height
            width: (root.width - idx.width)/ 4
            Text {
                id: syns
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
        }
        Rectangle {
            border.width: 1
            border.color: "black"
            height: root.height
            width: (root.width - idx.width) / 4
            Text {
                id: date
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
        }
    }
}












