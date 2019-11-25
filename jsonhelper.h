#ifndef JSONHELPER_H
#define JSONHELPER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>

class JSonHelper
{
    enum class Method {
        sign_up,
        sign_in
    };
    QString state;
public:
    QByteArray create_json_doc(const QString& user_name, const QString& user_password,
                               int method, const QString& file_name, qint64 length);
    QByteArray create_sing_in_up_doc(const QString& user_name, const QString& user_password, int method);
    bool is_json_obj(const QByteArray& data);
    QString get_state() const;
};

#endif // JSONHELPER_H
