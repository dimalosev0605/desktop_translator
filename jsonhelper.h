#ifndef JSONHELPER_H
#define JSONHELPER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>
#include "settings.h"

class JSonHelper
{
public:
    enum class Method {
        sign_up,
        sign_in,
        get_list_of_files,
        download_file,
        upload_file
    };

    enum class State {
        success_sign_up,
        unsuccess_sign_up,
        internal_server_error,
        success_sing_in,
        unsuccess_sing_in,
        ready_upload_file,
        success_uploading
    };
    State state;
    QList<std::pair<QString, QString>> list_of_files;
public:
    QByteArray create_json(Method method, const QString& user_name, const QString& user_password);
    QByteArray load_file_json(Method method, const QString& user_name, const QString& user_password, const QString& file_name, qint64 size);
    bool is_json(const QByteArray& data);
    State get_state() const;
    QList<std::pair<QString, QString>> get_list_of_files() const;
};

#endif // JSONHELPER_H
