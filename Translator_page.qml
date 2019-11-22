import QtQuick 2.11
import QtQuick.Controls 2.4
import Blocks_data_model_qml 1.0

Item {
    id: translator_page

    Menu_bar_in_translator {
        id: menu_bar
    }

    Blocks_data_model {
        id: blocks_data_model
    }

    TextField {
        id: user_input_field
        anchors.top: menu_bar.bottom
        anchors.topMargin: 20
        anchors.left: menu_bar.left
        anchors.leftMargin: 20
        height: 30
        width: translator_page.width / 6
        placeholderText: "Input text"
        onTextChanged: blocks_data_model.on_input_changed(user_input_field.text)
    }
    Item {
        id: repeating_text_space
        anchors.top: user_input_field.bottom
        anchors.topMargin: 10
        anchors.left: user_input_field.left
        anchors.right: clear_btn.right
        height: user_input_field.height
        Text {
            id: repeating_text
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            width: parent.width - edit_record_btn.width
            height: parent.height
            fontSizeMode: Text.Fit
            minimumPointSize: 5
            font.pointSize: 10
            elide: Text.ElideRight
            wrapMode: Text.WordWrap
            text: "LALALALAALALALAL"
        }
        Edit_record_btn {
            id: edit_record_btn
            anchors.right: repeating_text_space.right
            anchors.top: repeating_text_space.top
            height: repeating_text_space.height
            width: height
        }
    }
    TextField {
        id: means_field
        anchors.top: repeating_text_space.bottom
        anchors.topMargin: 10
        anchors.left: user_input_field.left
        anchors.right: clear_btn.right
        height: user_input_field.height
        placeholderText: "Input means"
    }
    TextField {
        id: translations_filed
        anchors.top: means_field.bottom
        anchors.topMargin: 10
        anchors.left: user_input_field.left
        anchors.right: clear_btn.right
        height: user_input_field.height
        placeholderText: "Input translations"
    }
    Translator_control {
        id: add_btn
        anchors.left: user_input_field.right
        anchors.leftMargin: 20
        anchors.top: user_input_field.top
        color: "#00ff00"
        text: "Add"
    }
    Translator_control {
        id: clear_btn
        anchors.left: add_btn.right
        anchors.leftMargin: 10
        anchors.top: add_btn.top
        color: "#ff0000"
        text: "Clear"
        mouse_area.onClicked: {
            user_input_field.clear()
            means_field.clear()
            translations_filed.clear()
        }
    }

    Shortcut {
        sequence: "Alt+C"
        onActivated: clear_btn.mouse_area.clicked(MouseArea)
    }


    Rectangle {
        id: blocks_scroll_view_frame
        anchors.top: translations_filed.bottom
        anchors.topMargin: 20
        anchors.bottom: translator_page.bottom
        anchors.bottomMargin: 5
        anchors.left: translations_filed.left
        width: translator_page.width / 2    // need consider anchors ???
        border.width: 1
        border.color: "black"
        ScrollView {
            id: blocks_scroll_view
            anchors.fill: parent
            ListView {
                anchors.fill: parent
                spacing: 10
                clip: true
                model: blocks_data_model
                delegate: Block_delegate {
                    transcription: String(model.transcription)
                    type_speech: String(model.type_speech)
                    syns: String(model.syns)
                    means: String(model.means)
                    examples: String(model.exaples)
                }
            }
        }
    }
    Rectangle {
        id: words_scroll_view_frame
        anchors.left: blocks_scroll_view_frame.right
        anchors.leftMargin: 20
        anchors.top: translations_filed.bottom
        anchors.topMargin: 20
        anchors.right: translator_page.right
        anchors.rightMargin: 20
        anchors.bottom: translator_page.bottom
        anchors.bottomMargin: 5
        border.width: 1
        border.color: "black"
    }
}































