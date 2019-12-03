#include "jsonhelper.h"

const QString name_key = "name";
const QString password_key = "password";
const QString method_key = "method";
const QString file_name_key = "file_name";
const QString length_key = "length";
const QString state_key = "state";
const QString files_key = "files";
const QString files_dates_key = "files_dates";

QByteArray JSonHelper::create_json(JSonHelper::Method method, const QString& user_name, const QString& user_password)
{
    QJsonObject obj;
    obj.insert(method_key, QJsonValue::fromVariant(static_cast<int>(method)));
    obj.insert(name_key, QJsonValue::fromVariant(user_name));
    obj.insert(password_key, QJsonValue::fromVariant(user_password));
    QJsonDocument doc(obj);
    return doc.toJson();
}

QByteArray JSonHelper::load_file_json(JSonHelper::Method method, const QString &user_name, const QString &user_password, const QString &file_name, qint64 size)
{
    QJsonObject obj;
    obj.insert(method_key, QJsonValue::fromVariant(static_cast<int>(method)));
    obj.insert(name_key, QJsonValue::fromVariant(user_name));
    obj.insert(password_key, QJsonValue::fromVariant(user_password));
    obj.insert(file_name_key, QJsonValue::fromVariant(file_name));
    obj.insert(length_key, QJsonValue::fromVariant(size));
    QJsonDocument doc(obj);
    return doc.toJson();
}

QByteArray JSonHelper::download_file_json(JSonHelper::Method method, const QString &user_name, const QString &user_password, const QString &file_name)
{
    QJsonObject obj;
    obj.insert(method_key, QJsonValue::fromVariant(static_cast<int>(method)));
    obj.insert(name_key, QJsonValue::fromVariant(user_name));
    obj.insert(password_key, QJsonValue::fromVariant(user_password));
    obj.insert(file_name_key, QJsonValue::fromVariant(file_name));
    QJsonDocument doc(obj);
    return doc.toJson();
}

QByteArray JSonHelper::create_state_json(JSonHelper::State state)
{
    QJsonObject obj;
    obj.insert(state_key, QJsonValue::fromVariant(static_cast<int>(state)));
    QJsonDocument doc(obj);
    return doc.toJson();
}

bool JSonHelper::is_json(const QByteArray &data)
{
    auto doc = QJsonDocument::fromJson(data);
    if(doc.isObject())
    {
        auto json_obj = doc.object();
        auto json_map = json_obj.toVariantMap();
        state = static_cast<State>(json_map[state_key].toInt());
        auto files = json_map[files_key].toJsonArray();
        auto files_dates = json_map[files_dates_key].toJsonArray();
        file_size = json_map[length_key].toLongLong();
        for(int i = 0; i < files.size(); ++i) {
            list_of_files.push_back({{files[i].toString()},{files_dates[i].toString()}});
        }
        return true;
    }
    else
    {
        return false;
    }
}

JSonHelper::State JSonHelper::get_state() const
{
    return state;
}

QList<std::pair<QString, QString>> JSonHelper::get_list_of_files() const
{
    return list_of_files;
}

qint64 JSonHelper::get_file_size() const
{
    return file_size;
}





















