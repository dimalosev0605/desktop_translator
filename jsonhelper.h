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
    enum class Token {
        sing_in = 0,
        sing_up,
        success_sing_in,
        unsuccess_sing_in,
        success_sing_up,
        unsuccess_sing_up,
        internal_server_error,
        upload_file,
        download_file,
        ready_upload_file,
        list_of_files,
        ready_send_file,
        ready_receive_file,
        delete_file
    };

    bool is_json(const QByteArray& data);
    QByteArray create_sing_in_up_json(const QString& user_name, const QString& user_password, Token token);
    QByteArray create_upload_file_json(const QString &user_name, const QString &file_name, qint64 file_size, JSonHelper::Token token);
    QByteArray create_list_of_files_json(const QString& user_name, Token token);
    QByteArray create_download_file_json(const QString& user_name, const QString& file_name, Token token);
    QByteArray create_ready_receive_file_json(const QString& user_name, const QString& file_name);
    QByteArray create_delete_file_json(const QString& user_name, const QString& file_name, Token token);
    Token get_token() const;
    QString get_files_str() const;
    qint64 get_file_size() const;
    void clear();

private:
    qint64 file_size;
    Token token;
    QString files_str;
};

#endif // JSONHELPER_H
