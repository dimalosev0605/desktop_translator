import QtQuick 2.11
import QtQuick.Controls 2.4
import Client_qml 1.0

Item {
    id: my_account_page

    Client {
        id: client
    }

    Universal_back_btn {
        id: back_btn
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    Column {
        anchors.centerIn: parent
        spacing: 10
        Label {
            id: info_lbl
            height: 30
            width: 200
            fontSizeMode: Text.Fit
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
            wrapMode: Text.WordWrap
            minimumPointSize: 5
            font.pointSize: 10
            text: "HELLOW!"
        }
        TextField {
            id: user_name
            height: info_lbl.height
            width: info_lbl.width
            placeholderText: "User name"
        }
        TextField {
            id: user_password
            height: info_lbl.height
            width: info_lbl.width
            placeholderText: "Password"
        }
        Row {
            spacing: 5
            Button {
                id: sign_up
                text: "Sign up"
                width: (info_lbl.width - 2 * spacing) / 3
                height: info_lbl.height
                onClicked: {
                    client.sign_up(user_name.text, user_password.text)
                }
            }
            Button {
                id: sign_in
                text: "Sign in"
                width: sign_up.width
                height: info_lbl.height
                onClicked: {
                    client.sign_in(user_name.text, user_password.text)
                }
            }
            Button {
                id: exit
                text: "Exit"
                width: sign_up.width
                height: info_lbl.height
            }
        }
    }

}














