import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

ApplicationWindow {
    id: app_window
    visible: true
    width: 640
    height: 480

    StackView {
        id: stack_view
        anchors.fill: parent
        initialItem: Initial_item_in_stack {}
    }
}
