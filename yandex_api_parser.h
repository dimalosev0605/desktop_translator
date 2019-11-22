#ifndef YANDEX_API_PARSER_H
#define YANDEX_API_PARSER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>
#include <QVector>
#include <QDebug>
#include "block.h"

class Yandex_api_parser
{
    QVector<Block> blocks;
public:
    Yandex_api_parser() = default;
    void parse(const QByteArray& data);
    QVector<Block>& get_blocks();
};

#endif // YANDEX_API_PARSER_H
