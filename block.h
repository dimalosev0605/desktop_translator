#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include <QDebug>

class Block
{
    QString type_speech;
    QString transcription;
    QString means;
    QString syns;
    QString examples;

    QString ex;
    QString ex_tr;

public:
    explicit Block() = default;
    Block(QString& t_s, QString& tr, QString& m, QString& s, QString& ex);
    void prepeare_block();
    void clear();
    void print_block() const;

    void set_type_speech(const QString& s);
    void set_transcription(const QString& s);
    void add_mean(const QString& s);
    void add_syn(const QString& s);
    void set_ex(const QString& s);
    void set_ex_tr(const QString& s);
    void make_example();

    QString get_type_speech() const;
    QString get_transcription() const;
    QString get_means() const;
    QString get_syns() const;
    QString get_examples() const;
};

#endif // BLOCK_H
