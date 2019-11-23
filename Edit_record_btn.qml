import QtQuick 2.11
import QtQuick.Controls 2.4

Control {
    id: control

    Rectangle {
        anchors.fill: parent
        color: control.hovered ? "#cfcfcf" : "white"
        Image {
            anchors.fill: parent
            source: "edit_icon.svg"
        }
        MouseArea {
            id: mouse_area
            anchors.fill: parent
            onClicked: {
                words_data_model.remove_word(words_data_model.get_repeating_index())
                repeating_text.text = ""
                user_input_field.text = words_data_model.word_get_word()
                means_field.text = words_data_model.word_get_means()
                translations_filed.text = words_data_model.word_get_syns()
            }
        }
    }
}
