import QtQuick 2.11
import QtQuick.Controls 2.4

Item {
    id: translator_page

    Menu_bar_in_translator {
        id: menu_bar
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
    }



}































