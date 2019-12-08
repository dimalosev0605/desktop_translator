import QtQuick 2.11
import QtQuick.Controls 2.4
import Client_qml 1.0

Item {
    id: my_account_page


    function wait_info_lbl () {
        info_lbl.text = "Please wait"
        pulsing_anim.running = true
    }

    Client {
        id: client
        onConnected_to_server: {
            info_lbl.visible = false
        }
        onServer_refused_connection: {
            pulsing_anim.running = false
            info_lbl.visible = true
            info_lbl.text = "Connection to server was refused. Try later."
        }
        onSuccess_sing_in: {
            settings.save_user_settings(user_name.text, user_password.text)
            info_lbl.text = "Success sing in!"
            info_lbl.visible = true
            pulsing_anim.running = false
            opacity_anim.start()
        }
        onUnsuccess_sing_in: {
            info_lbl.text = "Incorrect user name or password."
            info_lbl.visible = true
            pulsing_anim.running = false
            opacity_anim.start()
        }
        onSuccess_sing_up: {
            settings.save_user_settings(user_name.text, user_password.text)
            info_lbl.visible = true
            pulsing_anim.running = false
            info_lbl.text = "Success sing up!"
            opacity_anim.start()
        }
        onUnsuccess_sing_up: {
            info_lbl.text = "Such user already exist. Please change user name."
            info_lbl.visible = true
            pulsing_anim.running = false
            opacity_anim.start()
        }
        onInternal_server_error: {
            pulsing_anim.running = false
            info_lbl.visible = true
            info_lbl.text = "Internal server error. Try later."
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
            text: "Connecting to server..."
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
                    if(user_name.text === "" || user_password.text === "") return
                    if(client.sing_up(user_name.text, user_password.text)) {
                        wait_info_lbl()
                    }
                }
            }
            Button {
                id: sign_in
                text: "Sign in"
                width: sign_up.width
                height: info_lbl.height
                enabled: !settings.is_auth
                onClicked: {
                    if(user_name.text === "" || user_password.text === "") return
                    if(client.sing_in(user_name.text, user_password.text)) {
                        wait_info_lbl()
                    }
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














