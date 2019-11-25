#include "jsonhelper.h"

const QString name_key = "name";
const QString password_key = "password";
const QString method_key = "method";
const QString file_name_key = "file_name";
const QString length_key = "length";

QByteArray JSonHelper::create_json_doc(const QString &user_name, const QString &user_password,
                                       int method, const QString &file_name, qint64 length)
{
    QJsonObject obj;
    obj.insert(name_key, QJsonValue::fromVariant(user_name));
    obj.insert(password_key, QJsonValue::fromVariant(user_password));
    obj.insert(method_key, QJsonValue::fromVariant(method));
    obj.insert(file_name_key, QJsonValue::fromVariant(file_name));
    obj.insert(length_key, QJsonValue::fromVariant(length));
    QJsonDocument doc(obj);
    return doc.toJson();
}

QByteArray JSonHelper::create_sing_in_up_doc(const QString &user_name, const QString &user_password, int method)
{
    QJsonObject obj;
    obj.insert(name_key, QJsonValue::fromVariant(user_name));
    obj.insert(password_key, QJsonValue::fromVariant(user_password));
    obj.insert(method_key, QJsonValue::fromVariant(method));
    QJsonDocument doc(obj);
    return doc.toJson();
}

bool JSonHelper::is_json_obj(const QByteArray& data)
{
    auto json_doc = QJsonDocument::fromJson(data);
    if(json_doc.isObject())
    {
        auto json_obj = json_doc.object();
        auto json_map = json_obj.toVariantMap();
        state = json_map["state"].toString();
        return true;
    }
    else
    {
        return false;
    }
}

QString JSonHelper::get_state() const
{
    return state;
}














