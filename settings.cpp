#include "settings.h"

const QString user_name_key = "user_name";
const QString user_password_key = "user_password";

Settings::Settings(QObject *parent)
    : QObject (parent)
{
    load_user_settings();
}

void Settings::set_is_auth(bool v)
{
    is_auth = v;
    emit is_auth_changed();
}

bool Settings::get_is_auth() const
{
    return is_auth;
}

void Settings::save_user_settings(const QString &user_name, const QString &user_password)
{
    this->user_name = user_name;
    this->user_password = user_password;

    QJsonObject obj;
    obj.insert(user_name_key, QJsonValue::fromVariant(user_name));
    obj.insert(user_password_key, QJsonValue::fromVariant(user_password));
    QJsonDocument doc(obj);
    QFile file(file_manager.get_auth_file_path());
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(doc.toJson());
        set_is_auth(true);
    }
    file.close();
}

void Settings::delete_user_settings_and_files()
{
    user_name.clear();
    user_password.clear();
    QFile file(file_manager.get_auth_file_path());
    if(file.remove()) set_is_auth(false);
    QDir dir(file_manager.get_user_files_dir());
    dir.removeRecursively();
}

QString Settings::get_user_name() const
{
    return user_name;
}

QString Settings::get_user_password() const
{
    return user_password;
}

void Settings::load_user_settings()
{
    QFile file(file_manager.get_auth_file_path());
    if(file.open(QIODevice::ReadOnly))
    {
        auto json_doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        if(json_doc.isObject())
        {
            auto json_obj = json_doc.object();
            auto json_map = json_obj.toVariantMap();
            user_name = json_map[user_name_key].toString();
            user_password = json_map[user_password_key].toString();
            if(!user_name.isEmpty() && !user_password.isEmpty()) set_is_auth(true);
        }
    }
}























