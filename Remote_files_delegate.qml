import QtQuick 2.11
import QtQuick.Controls 2.4

Rectangle {
    id: root
    border.width: 1
    border.color: "black"
    width: remote_files_frame.width
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
            width: (root.width - idx_frame.width - delete_btn.width - download_btn.width) / 2
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
            color: delete_btn_m_a.containsMouse ? "#dedede" : "white"
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
                id: delete_btn_m_a
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    if(busy_indicator.running) return
                    if(client.delete_file(remote_files_model.get_file_name(index))) {
                        info_lbl.text = "Deleting..."
                        busy_indicator.visible = true
                        busy_indicator.running = true
                    }
                }
            }
        }
        Rectangle {
            id: download_btn
            border.width: 1
            border.color: "black"
            height: root.height
            width: delete_btn.width
            color: download_btn_m_a.containsMouse ? "#80ff4a" : "white"
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
                text: "Download"
            }
            MouseArea {
                id: download_btn_m_a
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    if(busy_indicator.running) return
                    if(client.download_file(remote_files_model.get_file_name(index))) {
                        info_lbl.text = "Downloading..."
                        busy_indicator.visible = true
                        busy_indicator.running = true
                    }
                }
            }
        }
    }

}
























