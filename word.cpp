#include "word.h"

Word::Word(const QString &w, const QString &t, const QString &m, const QString &s)
    : word (w),
      transcription (t),
      means (m),
      syns (s),
      date (QDate::currentDate())
{}

QString Word::get_word() const
{
    return word;
}

QString Word::get_transcription() const
{
    return transcription;
}

QString Word::get_means() const
{
    return means;
}

QString Word::get_syns() const
{
    return syns;
}

QDate Word::get_date() const
{
    return date;
}

QDataStream& operator<<(QDataStream& s, const Word& w)
{
    s << w.word << w.transcription << w.means << w.syns << w.date;
    return s;
}

QDataStream& operator>>(QDataStream& s, Word& w)
{
    s >> w.word >> w.transcription >> w.means >> w.syns >> w.date;
    return s;
}



