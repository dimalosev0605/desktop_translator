#include "blocks_data_model.h"

Blocks_data_model::Blocks_data_model(QObject *parent)
    : QAbstractListModel (parent)
{
    m_role_names[static_cast<int>(Role_names::type_speech)] = "type_speech";
    m_role_names[static_cast<int>(Role_names::transcription)] = "transcription";
    m_role_names[static_cast<int>(Role_names::means)] = "means";
    m_role_names[static_cast<int>(Role_names::syns)] = "syns";
    m_role_names[static_cast<int>(Role_names::examples)] = "exaples";

    connect(&yandex_api_connection, &Yandex_api_connection::blocks_ready, this, &Blocks_data_model::process_blocks);
}

QHash<int, QByteArray> Blocks_data_model::roleNames() const
{
    return m_role_names;
}

int Blocks_data_model::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return blocks.size();
}

QVariant Blocks_data_model::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= blocks.size()) return QVariant();

    switch(role)
    {
    case static_cast<int>(Role_names::type_speech):
        return blocks[row].get_type_speech();

    case static_cast<int>(Role_names::transcription):
        return blocks[row].get_transcription();

    case static_cast<int>(Role_names::means):
        return blocks[row].get_means();

    case static_cast<int>(Role_names::syns):
        return blocks[row].get_syns();

    case static_cast<int>(Role_names::examples):
        return blocks[row].get_examples();

    }

    return QVariant();
}

void Blocks_data_model::remove_all_rows()
{
    if(blocks.size() <= 0) return;
    beginRemoveRows(QModelIndex(), 0, blocks.size() - 1);
    blocks.clear();
    endRemoveRows();
}

void Blocks_data_model::insert_rows(int first, int last, QVector<Block>& v)
{
    if(last < 0) return;
    beginInsertRows(QModelIndex(), first, last);
    blocks = std::move(v);
    endInsertRows();
}


void Blocks_data_model::on_input_changed(const QString &user_input)
{
    yandex_api_connection.send_request_to_api_voc(user_input);
}

QString Blocks_data_model::get_transcription()
{
    if(blocks.empty()) return QString();
    return blocks[0].get_transcription();
}

void Blocks_data_model::change_from_lang(const QString &l)
{
    yandex_api_connection.change_from_lang(l);
}

void Blocks_data_model::change_on_lang(const QString &l)
{
    yandex_api_connection.change_on_lang(l);
}

QString Blocks_data_model::get_from_lang() const
{
    return yandex_api_connection.get_from_lang();
}

QString Blocks_data_model::get_on_lang() const
{
    return yandex_api_connection.get_on_lang();
}

void Blocks_data_model::process_blocks()
{
    auto temp = yandex_api_connection.get_blocks();
    remove_all_rows();
    insert_rows(0, temp.size() - 1, temp);
}






















