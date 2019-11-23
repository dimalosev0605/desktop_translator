#ifndef WORDS_DATA_MODEL_H
#define WORDS_DATA_MODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QVector>
#include "word.h"

class Words_data_model: public QAbstractListModel
{
    Q_OBJECT

    enum class Role_names {
        word = Qt::UserRole,
        transcription = Qt::UserRole + 1,
        means = Qt::UserRole + 2,
        syns = Qt::UserRole + 3,
        date = Qt::UserRole + 4
    };
    QHash<int, QByteArray> m_role_names;
    QHash<int, QByteArray> roleNames() const override;
    QVector <Word> words;
    Word word; // this word used for find_repeatind() and remove_word()
    int repeating_index = -1;
public:
    explicit Words_data_model(QObject* parent = nullptr);
    virtual int rowCount(const QModelIndex &index = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;

public slots:
    void add_word(const QString& w, const QString& tr, const QString& m, const QString& syns);
    void remove_word(int index);
    void find_repeating(const QString& word);

    QString word_get_word();
    QString word_get_means();
    QString word_get_syns();
    QString word_get_date();
    int get_repeating_index();
signals:
    void repeating_was_found();
};

#endif // WORDS_DATA_MODEL_H
