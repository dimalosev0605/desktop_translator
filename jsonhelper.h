#ifndef JSONHELPER_H
#define JSONHELPER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>

class JSonHelper
{
public:
    enum class Method {
        sign_up,
        sign_in
    };

    enum class State {
        success_sing_up,
        sign_up_conflict,
        success_sing_in,
        unlucky_sing_in,
        server_error
    };

    State state;
public:
    QByteArray create_json_doc(const QString& user_name, const QString& user_password,
                               int method, const QString& file_name, qint64 length);
    QByteArray create_sing_in_up_doc(const QString& user_name, const QString& user_password, Method method);
    bool is_json_obj(const QByteArray& data);
    State get_state() const;
};

#endif // JSONHELPER_H
