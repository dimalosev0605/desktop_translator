#include "jsonhelper.h"

const QString name_key = "name";
const QString password_key = "password";
const QString token_key = "token";

const QString file_name_key = "file_name";
const QString length_key = "length";
const QString state_key = "state";
const QString files_key = "files";
const QString files_dates_key = "files_dates";

bool JSonHelper::is_json(const QByteArray &data)
{
    auto doc = QJsonDocument::fromJson(data);
    if(!doc.isNull()) {
        auto json_obj = doc.object();
        auto json_map = json_obj.toVariantMap();
        token = static_cast<Token>(json_map[token_key].toInt());
        file_size = json_map[length_key].toLongLong();

        if(token == Token::list_of_files) {
            auto files = json_map[files_key].toJsonArray();
            auto files_dates = json_map[files_dates_key].toJsonArray();
            for(int i = 0; i < files.size(); ++i) {
                files_str.push_back(files[i].toString());
                files_str.push_back('#');
                files_str.push_back(files_dates[i].toString());
                files_str.push_back('#');
            }
            return true;
        }

        return true;
    }
    else {
        return false;
    }
}

QByteArray JSonHelper::create_sing_in_up_json(const QString &user_name, const QString &user_password, Token token)
{
    QJsonObject obj;
    obj.insert(token_key, static_cast<int>(token));
    obj.insert(name_key, user_name);
    obj.insert(password_key, user_password);

    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson();
}

QByteArray JSonHelper::create_upload_file_json(const QString &user_name, const QString &file_name, qint64 file_size, JSonHelper::Token token)
{
    QJsonObject obj;
    obj.insert(token_key, static_cast<int>(token));
    obj.insert(name_key, user_name);
    obj.insert(file_name_key, file_name);
    obj.insert(length_key, file_size);

    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson();
}

QByteArray JSonHelper::create_list_of_files_json(const QString &user_name, JSonHelper::Token token)
{
    QJsonObject obj;
    obj.insert(token_key, static_cast<int>(token));
    obj.insert(name_key, user_name);

    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson();
}

QByteArray JSonHelper::create_download_file_json(const QString &user_name, const QString& file_name, JSonHelper::Token token)
{
    QJsonObject obj;
    obj.insert(token_key, static_cast<int>(token));
    obj.insert(name_key, user_name);
    obj.insert(file_name_key, file_name);

    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson();
}

QByteArray JSonHelper::create_ready_receive_file_json(const QString& user_name, const QString& file_name)
{
    QJsonObject obj;
    obj.insert(token_key, static_cast<int>(Token::ready_receive_file));
    obj.insert(name_key, user_name);
    obj.insert(file_name_key, file_name);

    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson();
}

QByteArray JSonHelper::create_delete_file_json(const QString &user_name, const QString &file_name, JSonHelper::Token token)
{
    QJsonObject obj;
    obj.insert(token_key, static_cast<int>(token));
    obj.insert(name_key, user_name);
    obj.insert(file_name_key, file_name);

    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson();
}

JSonHelper::Token JSonHelper::get_token() const
{
    return token;
}

QString JSonHelper::get_files_str() const
{
    return files_str;
}

void JSonHelper::clear()
{
    files_str.clear();
    file_size = 0;
}

qint64 JSonHelper::get_file_size() const
{
    return file_size;
}








