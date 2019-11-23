#ifndef WORD_H
#define WORD_H

#include <QVector>
#include <QDate>

class Word
{
    QString word;
    QString transcription;
    QString means;
    QString syns;
    QDate date;

public:
    Word() = default;
    Word(const QString& w, const QString& t, const  QString& m, const  QString& s);

    QString get_word() const;
    QString get_transcription() const;
    QString get_means() const;
    QString get_syns() const;
    QDate get_date() const;

    friend QDataStream& operator<<(QDataStream& s, const Word& w);
    friend QDataStream& operator>>(QDataStream& s, Word& w);
};

#endif // WORD_H
