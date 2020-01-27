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


QByteArray JSonHelper::create_json(Token token, const QString& user_name, const QString& user_password, const QString& file_name, const qint64 file_size)
{
    QJsonObject obj;

    obj.insert(token_key, static_cast<int>(token));
    obj.insert(name_key, user_name);

    if(token == Token::sing_in || token == Token::sing_up) {
        obj.insert(password_key, user_password);
    }
    if(token == Token::upload_file) {
        obj.insert(file_name_key, file_name);
        obj.insert(length_key, file_size);
    }
    if(token == Token::download_file || token == Token::delete_file || token == Token::ready_receive_file) {
        obj.insert(file_name_key, file_name);
    }

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








