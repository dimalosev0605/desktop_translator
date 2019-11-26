import QtQuick 2.11
import Settings_qml 1.0

Item {

    Settings {
        id: settings
    }

    Column {
        anchors.centerIn: parent
        spacing: 10
        Component {
            id: translator_page_comp
            Translator_page {
                id: translator_page
                Component.onDestruction: print("Destroying translator page.")
            }
        }
        Initial_item_btn {
            id: translator_btn
            text: "Translator"
            mouse_area.onClicked: stack_view.push(translator_page_comp)
        }
        Initial_item_btn {
            id: cloud_btn
            text: "Cloud"
            enabled: settings.get_user_name() === "" ? false : true
            mouse_area.onClicked: stack_view.push("")
        }
        Component {
            id: my_account_page_comp
            My_account_page {
                id: my_account_page
                Component.onDestruction: print("Destroying my account page.")
            }
        }
        Initial_item_btn {
            id: my_account_btn
            text: "My account"
            mouse_area.onClicked: stack_view.push(my_account_page_comp)
        }
        Initial_item_btn {
            id: exit_btn
            text: "Exit"
            mouse_area.onClicked: Qt.quit()
        }
    }
}
