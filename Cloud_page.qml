import QtQuick 2.11
import QtQuick.Controls 2.4
import LocalFilesDataModel_qml 1.0
import RemoteFilesDataModel_qml 1.0
import Client_qml 1.0

Item {
    id: cloud_page

    Universal_back_btn {
        id: back_btn
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    Client {
        id: client
        onInternal_server_error: {
            // TODO
        }
        onList_of_files: {
            //Success uploading (or success deleting) need update padding of remote files model
            remote_files_model.receive_list_of_files(list)
            busy_indicator.visible = false
            busy_indicator.running = false
        }
        onConnected_to_server: {
            busy_indicator.visible = false
            busy_indicator.running = false
        }
        onServer_refused_connection: {
            busy_indicator.visible = false
            busy_indicator.running = false
            info_lbl.text = "Connection to server was refused. Try later."
            info_lbl.visible = true
        }
        onSuccess_downloading: {
            busy_indicator.visible = false
            busy_indicator.running = false
            local_files_model.update_data()
        }
        onUnsuccess_downloading: {
            // TODO
//            busy_indicator.visible = false
//            busy_indicator.running = false
//            info_lbl.text = "unsuccessful loading."
        }
    }

    LocalFilesDataModel {
        id: local_files_model
    }
    RemoteFilesDataModel {
        id: remote_files_model
    }

    BusyIndicator {
        id: busy_indicator
        running: true
        anchors.centerIn: remote_files_frame
        visible: true
        z: 3
    }
    Label {
        id: info_lbl
        text: "Connecting to server..."
        z: 3
        visible: busy_indicator.running
        anchors.horizontalCenter: busy_indicator.horizontalCenter
        anchors.top: busy_indicator.bottom
        height: 40
        width: 200
        fontSizeMode: Text.Fit
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideRight
        wrapMode: Text.WordWrap
        minimumPointSize: 5
        font.pointSize: 12
        SequentialAnimation {
            id: pulsing_anim
            loops: Animation.Infinite
            running: busy_indicator.running
            OpacityAnimator {
                target: info_lbl
                from: 1
                to: 0
                duration: 2000
            }
            OpacityAnimator {
                target: info_lbl
                from: 0
                to: 1
                duration: 2000
            }
        }
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
        width: (cloud_page.width - back_btn.anchors.leftMargin * 3) / 2 // left, right margins between frame and window and the last one is the margin between frames.
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
        ScrollView {
            anchors.fill: parent
            ListView {
                id: remote_files_view
                anchors.fill: parent
                spacing: 10
                clip: true
                model: remote_files_model
                delegate: Remote_files_delegate {
                    file_name: String(model.file_name)
                    modified_date: String(model.modified_date)
                }
            }
        }
    }

}




























