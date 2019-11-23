#include "words_data_model.h"

Words_data_model::Words_data_model(QObject *parent)
    : QAbstractListModel (parent)
{
    m_role_names[static_cast<int>(Role_names::word)] = "word";
    m_role_names[static_cast<int>(Role_names::transcription)] = "transcription";
    m_role_names[static_cast<int>(Role_names::means)] = "means";
    m_role_names[static_cast<int>(Role_names::syns)] = "syns";
    m_role_names[static_cast<int>(Role_names::date)] = "date";
}

QHash<int, QByteArray> Words_data_model::roleNames() const
{
    return m_role_names;
}


int Words_data_model::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return words.size();
}

QVariant Words_data_model::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= words.size()) return QVariant();

    switch(role)
    {
    case static_cast<int>(Role_names::word):
        return words[row].get_word();

    case static_cast<int>(Role_names::transcription):
        return words[row].get_transcription();

    case static_cast<int>(Role_names::means):
        return words[row].get_means();

    case static_cast<int>(Role_names::syns):
        return words[row].get_syns();

    case static_cast<int>(Role_names::date):
        return words[row].get_date().toString("d.MM.yy");

    }

    return QVariant();
}

void Words_data_model::add_word(const QString &w, const QString &tr, const QString &m, const QString &syns)
{
    beginInsertRows(QModelIndex(), words.size(), words.size());
    words.push_back(Word(w, tr, m, syns));
    endInsertRows();
}

void Words_data_model::remove_word(int index)
{
    if(index < 0 || index >= words.size()) return;

    repeating_index = -1;
    word = Word(words[index].get_word(), words[index].get_transcription(),
                words[index].get_means(), words[index].get_syns());

    beginRemoveRows(QModelIndex(), index, index);
    words.removeAt(index);
    endRemoveRows();
}

void Words_data_model::find_repeating(const QString &word)
{
    if(word.isEmpty()) return;
    repeating_index = 0;
    for(; repeating_index < words.size(); ++repeating_index)
    {
        if(words[repeating_index].get_word() == word)
        {
            this->word = words[repeating_index];
            emit repeating_was_found();
            return;
        }
    }
    repeating_index = -1;
}

QString Words_data_model::word_get_word()
{
    return word.get_word();
}

QString Words_data_model::word_get_means()
{
    return word.get_means();
}

QString Words_data_model::word_get_syns()
{
    return word.get_syns();
}

QString Words_data_model::word_get_date()
{
    return word.get_date().toString("d.MM.yy");
}

int Words_data_model::get_repeating_index()
{
    return repeating_index;
}
















