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
        upload_file,
        initial,
        delete_file
    };

    enum class State {
        success_sign_up,
        unsuccess_sign_up,
        internal_server_error,
        success_sing_in,
        unsuccess_sing_in,
        ready_upload_file,
        success_uploading,
        ready_download_file,
        success_deletion
    };
    State state;
    QList<std::pair<QString, QString>> list_of_files;
    qint64 file_size;
public:
    QByteArray create_json(Method method, const QString& user_name, const QString& user_password, const QString& file_name, qint64 size);
    QByteArray create_state_json(State state);
    bool is_json(const QByteArray& data);
    State get_state() const;
    qint64 get_file_size() const;
    QList<std::pair<QString, QString>> get_list_of_files() const;
    void clear();
};

#endif // JSONHELPER_H
