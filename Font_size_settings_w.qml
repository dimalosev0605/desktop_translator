import QtQuick 2.9
import QtQuick.Controls 2.4

ApplicationWindow {
    id: font_size_settings_w

    onClosing: font_size_settings_w.destroy()

    width: 400
    height: 300
    title: "Font-size"

    Row {
        anchors.centerIn: parent
        spacing: 5
        Column {
            spacing: 5
            Text {
                text: "Fields:"
                height: text_fieds_slider.height
                font.pointSize: 10
            }
            Text {
                text: "Translations:"
                height: text_fieds_slider.height
                font.pointSize: 10
            }
            Text {
                text: "Your words:"
                height: text_fieds_slider.height
                font.pointSize: 10
            }
        }
        Column {
            spacing: 5
            Font_size_slider {
                id: text_fieds_slider
                value: user_input_field.font.pointSize
                onValueChanged: {
                    user_input_field.font.pointSize = value
                    means_field.font.pointSize = value
                    translations_filed.font.pointSize = value
                }
            }
            Font_size_slider {
                id: blocks_slider
                value: blocks_list_view.font_size
                onValueChanged: {
                    blocks_list_view.font_size = value
                }
            }
            Font_size_slider {
                id: words_slider
                value: words_list_view.font_size
                onValueChanged: {
                    words_list_view.font_size = value
                }
            }
        }
    }

}



















