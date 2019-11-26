import QtQuick 2.11
import QtQuick.Controls 2.4
import LocalFilesDataModel_qml 1.0

Item {
    id: cloud_page

    Universal_back_btn {
        id: back_btn
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    LocalFilesDataModel {
        id: local_files_model
    }

    Text {
        id: locale_files_lbl
        anchors.top: back_btn.bottom
        anchors.topMargin: 10
        x: cloud_page.width / 2 / 2 - width / 2
        text: "Files on your computer"
        font.pointSize: 10
    }

    Rectangle {
        id: locale_files_frame
        anchors.left: back_btn.left
        anchors.top: locale_files_lbl.bottom
        anchors.topMargin: 10
        border.width: 1
        border.color: "black"
        width: (cloud_page.width - back_btn.anchors.leftMargin * 3) / 2 // two are left, right margins between frame and window and the last one is the margin between frames.
        height: 300
        ScrollView {
            anchors.fill: parent
            ListView {
                id: local_files_view
                anchors.fill: parent
                spacing: 10
                clip: true
                model: local_files_model
                delegate: Local_files_delegate {
                    file_name: String(model.file_name)
                    modified_date: String(model.modified_date)
                }
            }
        }
    }

    Text {
        id: remote_files_lbl
        anchors.top: locale_files_lbl.top
        x: cloud_page.width * 3 / 4 - width / 2
        text: "Files on server"
        font.pointSize: 10
    }

    Rectangle {
        id: remote_files_frame
        border.width: 1
        border.color: "black"
        anchors.left: locale_files_frame.right
        anchors.leftMargin: 10
        anchors.top: locale_files_frame.top
        width: locale_files_frame.width
        height: 300
    }

}




























