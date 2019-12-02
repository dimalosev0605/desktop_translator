import QtQuick 2.11
import QtQuick.Controls 2.4
import Client_qml 1.0

Item {
    id: my_account_page

    Client {
        id: client
        onConnected_to_server: {
            pulsing_anim.stop()
            info_lbl.text = ""
        }
        onSuccess_sing_up: {
            info_lbl.text = "Success sign up"
            settings.save_user_settings(user_name.text, user_password.text)
            opacity_anim.start()
        }
        onUnsuccess_sing_up: {
            info_lbl.text = "Such user name already exists."
            opacity_anim.start()
        }
        onSuccess_sing_in: {
            info_lbl.text = "Success sign in"
            settings.save_user_settings(user_name.text, user_password.text)
            opacity_anim.start()
        }
        onUnsuccess_sing_in: {
            info_lbl.text = "Incorrect name or password"
            opacity_anim.start()
        }
        onInternal_server_error: {
            info_lbl.text = "Internal server error"
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
            text: "Connecting to server"
            OpacityAnimator {
                id: opacity_anim
                target: info_lbl
                from: 1
                to: 0
                duration: 3000
                running: false
            }
            SequentialAnimation {
                id: pulsing_anim
                loops: Animation.Infinite
                running: true
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
                enabled: !settings.is_auth
                onClicked: {
                    client.sing_up_f(user_name.text, user_password.text)
                }
            }
            Button {
                id: sign_in
                text: "Sign in"
                width: sign_up.width
                height: info_lbl.height
                enabled: !settings.is_auth
                onClicked: {
                    client.sing_in_f(user_name.text, user_password.text)
                }
            }
            Button {
                id: exit
                text: "Exit"
                width: sign_up.width
                height: info_lbl.height
                enabled: settings.is_auth
                onClicked: {
                    settings.delete_user_settings_and_files()
                    user_name.text = ""
                    user_password.text = ""
                }
            }
        }
    }

}














