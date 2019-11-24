#ifndef BLOCKS_DATA_MODEL_H
#define BLOCKS_DATA_MODEL_H

#include <QAbstractListModel>
#include "block.h"
#include "yandex_api_connection.h"

class Blocks_data_model: public QAbstractListModel
{
    Q_OBJECT

    enum class Role_names {
        type_speech =  Qt::UserRole,
        transcription = Qt::UserRole + 1,
        means =  Qt::UserRole + 2,
        syns =  Qt::UserRole + 3,
        examples =  Qt::UserRole + 4
    };
    QHash<int, QByteArray> m_role_names;
    QHash<int, QByteArray> roleNames() const override;
    QVector<Block> blocks;
    Yandex_api_connection yandex_api_connection;

private slots:
    void process_blocks();

public:
    explicit Blocks_data_model(QObject* parent = nullptr);
    virtual int rowCount(const QModelIndex &index = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;

    void remove_all_rows();
    void insert_rows(int first, int last, QVector<Block>& v);

public slots:
    void on_input_changed(const QString& user_input);
    QString get_transcription(); // God forgive me
    void change_from_lang(const QString& l);
    void change_on_lang(const QString& l);
    QString get_from_lang() const;
    QString get_on_lang() const;
};

#endif // BLOCKS_DATA_MODEL_H


















