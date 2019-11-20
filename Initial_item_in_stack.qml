import QtQuick 2.11

Item {
    Column {
        anchors.centerIn: parent
        spacing: 10
        Initial_item_btn {
            id: translator_btn
            text: "Translator"
            mouse_area.onClicked: stack_view.push("qrc:/Translator_page.qml")
        }
        Initial_item_btn {
            id: my_files_btn
            text: "My files"
            mouse_area.onClicked: stack_view.push("")
        }
        Initial_item_btn {
            id: my_account_btn
            text: "My account"
            mouse_area.onClicked: stack_view.push("")
        }
        Initial_item_btn {
            id: exit_btn
            text: "Exit"
            mouse_area.onClicked: Qt.quit()
        }
    }
}
