import QtQuick 2.11
import QtQuick.Controls 2.4
import Client_qml 1.0

Item {
    id: my_account_page

    Client {
        id: client
        onSuccess_sing_up: {
            settings.save_user_settings(user_name.text, user_password.text)
            sign_in.enabled = false
            sign_up.enabled = false
            user_name.enabled = false
            user_password.enabled = false
            exit.enabled = true
            info_lbl.text = "Success sing up!"
            opacity_anim.start()
        }
        onSuccess_sign_in: {
            settings.save_user_settings(user_name.text, user_password.text)
            sign_in.enabled = false
            sign_up.enabled = false
            user_name.enabled = false
            user_password.enabled = false
            exit.enabled = true
            info_lbl.text = "Success sing in!"
            opacity_anim.start()
        }
        onSign_up_conflict: {
            info_lbl.text = "Such user already exists. Change user name."
            opacity_anim.start()
        }
        onUnlucky_sing_in: {
            info_lbl.text = "Incorrect name or password"
            opacity_anim.start()
        }
        onServer_error: {
            info_lbl.text = "Server error occurred."
            opacity_anim.start()
        }
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
            OpacityAnimator {
                id: opacity_anim
                target: info_lbl
                from: 1
                to: 0
                duration: 3000
                running: false
            }
        }
        TextField {
            id: user_name
            height: info_lbl.height
            width: info_lbl.width
            placeholderText: "User name"
            text: settings.get_user_name()
            enabled: sign_up.enabled
        }
        TextField {
            id: user_password
            height: info_lbl.height
            width: info_lbl.width
            placeholderText: "Password"
            text: settings.get_user_password()
            enabled: sign_up.enabled
        }
        Row {
            spacing: 5
            Button {
                id: sign_up
                text: "Sign up"
                width: (info_lbl.width - 2 * spacing) / 3
                height: info_lbl.height
                enabled: settings.get_user_name() === "" ? true : false
                onClicked: {
                    client.sign_up(user_name.text, user_password.text)
                }
            }
            Button {
                id: sign_in
                text: "Sign in"
                width: sign_up.width
                height: info_lbl.height
                enabled: settings.get_user_name() === "" ? true : false
                onClicked: {
                    client.sign_in(user_name.text, user_password.text)
                }
            }
            Button {
                id: exit
                text: "Exit"
                width: sign_up.width
                height: info_lbl.height
                enabled: settings.get_user_name() === "" ? false : true
                onClicked: {
                    settings.delete_user_settings_and_files()
                    user_name.text = ""
                    user_password.text = ""
                    sign_in.enabled = true
                    sign_up.enabled = true
                    user_name.enabled = true
                    user_password.enabled = true
                    exit.enabled = false
                }
            }
        }
    }

}














