#include "yandex_api_connection.h"

Yandex_api_connection::Yandex_api_connection(QObject *parent)
    : QObject (parent)
{
    connect(&network_manager, &QNetworkAccessManager::finished, this, &Yandex_api_connection::receive_data_from_api_voc);
    set_full_requset_string();
}

void Yandex_api_connection::send_request_to_api_voc(const QString &user_input)
{
    request.setUrl(QUrl(full_requset_string + user_input));
    network_manager.get(request);
}

QVector<Block>& Yandex_api_connection::get_blocks()
{
    return blocks;
}

void Yandex_api_connection::set_full_requset_string()
{
    full_requset_string = url_api_voc + key + lang_key_word + from_lang + '-' + to_lang + text_key_word;
}

void Yandex_api_connection::receive_data_from_api_voc(QNetworkReply *reply)
{
    if(reply->isFinished())
    {
        if(reply->error() == QNetworkReply::NoError)
        {
            parser.parse(QString::fromUtf8(reply->readAll()).toUtf8());
            blocks = parser.get_blocks(); // move ???
            emit blocks_ready();
        }
        else
        {
            blocks.clear();
            emit blocks_ready();
        }
    }
    reply->deleteLater();
}















