import QtQuick 2.11
import QtQuick.Controls 2.4

Rectangle {
    id: root
    border.width: 1
    border.color: "black"
    width: locale_files_frame.width
    height: 30

    property alias file_name: file_name_text.text
    property alias modified_date: modified_date_text.text

    Row {
        Rectangle {
            id: idx_frame
            border.width: 1
            border.color: "black"
            height: root.height
            width: 30
            Text {
                id: idx
                text: index + 1
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
                height: parent.height
                fontSizeMode: Text.Fit
                minimumPointSize: 5
                font.pointSize: 10
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
            }
        }
        Rectangle {
            id: file_name_frame
            border.width: 1
            border.color: "black"
            height: root.height
            width: (root.width - idx_frame.width - delete_btn.width - upload_btn.width) / 2
            Text {
                id: file_name_text
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
                height: parent.height
                fontSizeMode: Text.Fit
                minimumPointSize: 5
                font.pointSize: 10
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
            }
        }
        Rectangle {
            id: modified_date_rect
            border.width: 1
            border.color: "black"
            height: root.height
            width: file_name_frame.width
            Text {
                id: modified_date_text
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
                height: parent.height
                fontSizeMode: Text.Fit
                minimumPointSize: 5
                font.pointSize: 10
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
            }
        }
        Rectangle {
            id: delete_btn
            border.width: 1
            border.color: "black"
            height: root.height
            width: 70
            color: delete_btn_m_area.containsMouse ? "#dedede" : "white"
            Text {
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
                height: parent.height
                fontSizeMode: Text.Fit
                minimumPointSize: 5
                font.pointSize: 10
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
                text: "Delete"
            }
            MouseArea {
                id: delete_btn_m_area
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    local_files_model.delete_file(index)
                }
            }
        }
        Rectangle {
            id: upload_btn
            border.width: 1
            border.color: "black"
            height: root.height
            width: delete_btn.width
            color: upload_btn_m_area.containsMouse ? "#80ff4a" : "white"
            Text {
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
                height: parent.height
                fontSizeMode: Text.Fit
                minimumPointSize: 5
                font.pointSize: 10
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
                text: "Upload"
            }
            MouseArea {
                id: upload_btn_m_area
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    if(busy_indicator.running) return
                    if(client.upload_file(local_files_model.get_file_name(index))) {
                        info_lbl.text = "Uploading..."
                        busy_indicator.visible = true
                        busy_indicator.running = true
                    }
                }
            }
        }
    }
}













