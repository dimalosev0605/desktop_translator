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
    QByteArray create_json(Token token, const QString& user_name, const QString& user_password = "", const QString& file_name = "", const qint64 file_size = 0);

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
