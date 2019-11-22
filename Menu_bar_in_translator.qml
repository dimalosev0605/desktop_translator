import QtQuick 2.11
import QtQuick.Controls 2.4

Item {
    id: root
    width: translator_page.width
    height: 32

    Row {
        anchors.fill: parent
        spacing: 5
        Universal_back_btn {
            id: back_btn
        }
        Menu_bar_item {
            img.source: "my_files_icon.svg"
            mouse_area.onClicked: file_menu.open()
            Menu {
                id: file_menu
                y: parent.height
                width: 100
                property int count_of_items: 2
                height: count_of_items * 30
                Menu_item {
                    img.source: "open_file_icon.svg"
                    text: "Open"
//                    mouse_area.onClicked:
                }
                Menu_item {
                    img.source: "save_file_icon.svg"
                    text: "Save"
//                    mouse_area.onClicked:
                }
            }
        }
        Menu_bar_item {
            img.source: "settings_btn_icon.svg"
            mouse_area.onClicked: options_menu.open()
            Menu {
                id: options_menu
                y: parent.height
                width: 100
                property int count_of_items: 3
                height: count_of_items * 30
                Menu_item {
                    img.source: "language_icon.svg"
                    text: "Langs"
//                    mouse_area.onClicked:
                }
                Menu_item {
                    img.source: "font-size_icon.svg"
                    text: "Font"
//                    mouse_area.onClicked:
                }
                Menu_item {
                    img.source: "about_icon.svg"
                    text: "About"
//                    mouse_area.onClicked:
                }
            }
        }
    }

    Rectangle {
        id: line
        anchors.bottom: root.bottom
        width: root.width
        height: 2
        color: "#00ff00"
    }

}

















