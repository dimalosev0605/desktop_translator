#ifndef YANDEX_API_CONNECTION_H
#define YANDEX_API_CONNECTION_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QNetworkReply>
#include "yandex_api_parser.h"

class Yandex_api_connection: public QObject
{
    Q_OBJECT

    QNetworkAccessManager network_manager;
    QNetworkRequest request;

    const QString url_api_voc = "https://dictionary.yandex.net/api/v1/dicservice.json/lookup?key=";
    const QString lang_key_word = "&lang=";
    const QString text_key_word = "&text=";
    QString key = "dict.1.1.20190429T081339Z.b542d94a3bd6e94c.44ba397a59fa5a8a20131d6e4935837e898225df";
    QString from_lang = "en";
    QString to_lang = "ru";
    QString full_requset_string;

    Yandex_api_parser parser;
    QVector<Block> blocks;

    void set_full_requset_string();

private slots:
    void receive_data_from_api_voc(QNetworkReply* reply);

public:
    explicit Yandex_api_connection(QObject* parent = nullptr);
    void send_request_to_api_voc(const QString& user_input);
    QVector<Block>& get_blocks();

signals:
    void blocks_ready();

};

#endif // YANDEX_API_CONNECTION_H
