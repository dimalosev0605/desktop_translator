import QtQuick 2.11
import QtQuick.Controls 2.4
import Blocks_data_model_qml 1.0
import Words_data_model_qml 1.0

Item {
    id: translator_page

    function show_font_size_settings_w()
    {
        var component = Qt.createComponent("Font_size_settings_w.qml")
        var window = component.createObject(translator_page)
        window.show()
    }

    function show_change_langs_w()
    {
        var component = Qt.createComponent("Change_langs_w.qml")
        var window = component.createObject(translator_page)
        window.show()
    }

    Menu_bar_in_translator {
        id: menu_bar
    }

    Blocks_data_model {
        id: blocks_data_model
    }

    Words_data_model {
        id: words_data_model
        onRepeating_was_found: {
            repeating_text.text = words_data_model.word_get_word() + " " +
                    words_data_model.word_get_means() + " " + words_data_model.word_get_syns() + " " +
                    words_data_model.word_get_date()
        }
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
        KeyNavigation.tab: means_field
        font.pointSize: 10
        onTextChanged: {
            blocks_data_model.on_input_changed(user_input_field.text)
            repeating_text.text = ""
            words_data_model.find_repeating(user_input_field.text)
        }
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
        }
        Edit_record_btn {
            id: edit_record_btn
            visible: (repeating_text.text === "") ? false : true
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
        KeyNavigation.tab: translations_filed
        font.pointSize: 10
    }
    TextField {
        id: translations_filed
        anchors.top: means_field.bottom
        anchors.topMargin: 10
        anchors.left: user_input_field.left
        anchors.right: clear_btn.right
        height: user_input_field.height
        placeholderText: "Input translations"
        KeyNavigation.tab: blocks_list_view
        font.pointSize: 10
    }
    Translator_control {
        id: add_btn
        anchors.left: user_input_field.right
        anchors.leftMargin: 20
        anchors.top: user_input_field.top
        color: "#00ff00"
        text: "Add"
        mouse_area.onClicked: {
            words_data_model.add_word(user_input_field.text, blocks_data_model.get_transcription(),
                                      means_field.text, translations_filed.text)
            clear_btn.mouse_area.clicked(MouseArea)
        }
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
    Shortcut {
        sequence: "Alt+A"
        onActivated: add_btn.mouse_area.clicked(MouseArea)
    }
    Shortcut {
        sequence: "Alt+E"
        onActivated: edit_record_btn.mouse_area.clicked(MouseArea)
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
            anchors.fill: parent
            ListView {
                id: blocks_list_view
                anchors.fill: parent
                spacing: 10
                clip: true
                KeyNavigation.tab: user_input_field
                highlightMoveVelocity: 800
                model: blocks_data_model
                property int font_size: 10
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
        ScrollView {
            anchors.fill: parent
            ListView {
                id: words_list_view
                anchors.fill: parent
                spacing: 10
                clip: true
                model: words_data_model
                property int font_size: 10
                onCountChanged: {
                    currentIndex = count - 1
                }
                delegate: Word_delegate {
                    word_and_transcription: String(model.word + " " + model.transcription)
                    means: String(model.means)
                    syns: String(model.syns)
                    date: String(model.date)
                }
            }
        }
    }
}































