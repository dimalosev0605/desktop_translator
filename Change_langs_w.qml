import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
    id: change_langs_w

    onClosing: change_langs_w.destroy()

    width: row.width
    maximumWidth: width
    height: 300
    maximumHeight: height
    title: "Change languages"

    Row {
        id: row
        spacing: 10
        ComboBox {
            id: from_lang
            model: ["en", "ru", "es", "fr", "de"]
            displayText: blocks_data_model.get_from_lang()
            onActivated: {
                blocks_data_model.change_from_lang(currentText)
                displayText = blocks_data_model.get_from_lang()
            }
        }
        Image {
            id: img
            width: 30
            height: 30
            source: "change_langs_icon.svg"
        }
        ComboBox {
            id: on_lang
            model: ["en", "ru", "es", "fr", "de"]
            displayText: blocks_data_model.get_on_lang()
            onActivated: {
                blocks_data_model.change_on_lang(currentText)
                displayText = blocks_data_model.get_on_lang()
            }
        }
    }
}
