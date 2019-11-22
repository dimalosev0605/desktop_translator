#include "block.h"


Block::Block(QString &t_s, QString &tr, QString &m, QString &s, QString &ex)
    : type_speech (std::move(t_s)),
      transcription (std::move(tr)),
      means (std::move(m)),
      syns (std::move(s)),
      examples (std::move(ex))
{}

void Block::prepeare_block()
{
    means.chop(2);
    syns.chop(2);
    examples.chop(1);
}

void Block::clear()
{
    means.clear();
    syns.clear();
    examples.clear();
}

void Block::print_block() const
{
    qDebug() << "########BLOCK########";
    qDebug() << type_speech;
    qDebug() << transcription;
    qDebug() << means;
    qDebug() << syns;
    qDebug() << examples;
    qDebug() << "########BLOCK########";
}

void Block::set_type_speech(const QString &s)
{
    type_speech = s;
}

void Block::set_transcription(const QString &s)
{
    transcription = '[' + s + ']';
}

void Block::add_mean(const QString &s)
{
    means += s + ", ";
}

void Block::add_syn(const QString &s)
{
    syns += s + ", ";
}

void Block::set_ex(const QString &s)
{
    ex = s;
}

void Block::set_ex_tr(const QString &s)
{
    ex_tr = s;
}

void Block::make_example()
{
    examples += ex + " - " + ex_tr + '\n';
}


QString Block::get_type_speech() const
{
    return type_speech;
}

QString Block::get_transcription() const
{
    return transcription;
}

QString Block::get_means() const
{
    return means;
}

QString Block::get_syns() const
{
    return syns;
}

QString Block::get_examples() const
{
    return examples;
}
