#include "yandex_api_parser.h"


void Yandex_api_parser::parse(const QByteArray &data)
{
    blocks.clear();

    auto json_doc = QJsonDocument::fromJson(data);
    auto json_obj = json_doc.object();
    auto json_map = json_obj.toVariantMap();
    auto def_arr = json_map["def"].toJsonArray();

    for(int i = 0; i < def_arr.size(); ++i)
    {
        auto obj = def_arr[i].toObject();
        auto map = obj.toVariantMap();
        auto trs = map["tr"].toJsonArray();

        Block block;
        block.set_transcription(map["ts"].toString());

        for(int i = 0; i < trs.size(); ++i)
        {
            auto obj = trs[i].toObject();
            auto map = obj.toVariantMap();
            block.add_syn(map["text"].toString());
            block.set_type_speech(map["pos"].toString());

            auto syns = map["syn"].toJsonArray();
            for(int i = 0; i < syns.size(); ++i)
            {
                auto obj = syns[i].toObject();
                auto map = obj.toVariantMap();
                block.add_syn(map["text"].toString());
            }
            auto means = map["mean"].toJsonArray();
            for(int i = 0; i < means.size(); ++i)
            {
                auto obj = means[i].toObject();
                auto map = obj.toVariantMap();
                block.add_mean(map["text"].toString());
            }
            auto examples = map["ex"].toJsonArray();
            for(int i = 0; i < examples.size(); ++i)
            {
                auto obj = examples[i].toObject();
                auto map = obj.toVariantMap();
                block.set_ex(map["text"].toString());
                auto ex_tr = map["tr"].toJsonArray();
                for(int i = 0; i < ex_tr.size(); ++i)
                {
                    auto obj = ex_tr[i].toObject();
                    auto map = obj.toVariantMap();
                    block.set_ex_tr(map["text"].toString());
                }
                block.make_example();
            }
            block.prepeare_block();
            blocks.push_back(block);
            block.clear();
        }
    }
}

QVector<Block> &Yandex_api_parser::get_blocks()
{
    return blocks;
}
