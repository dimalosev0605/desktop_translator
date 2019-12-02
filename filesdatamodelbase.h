#ifndef FILESDATAMODELBASE_H
#define FILESDATAMODELBASE_H

#include <QObject>
#include <QAbstractListModel>

class FilesDataModelBase: public QAbstractListModel
{
    Q_OBJECT

    enum class RolesNames {
        file_name = Qt::UserRole,
        modified_date = Qt::UserRole + 1
    };

    QHash<int, QByteArray> m_roleNames;
    QHash<int, QByteArray> roleNames() const override;

protected:
    QVector<std::pair<QString, QString>> files;

public:
    explicit FilesDataModelBase(QObject* parent = nullptr);
    virtual int rowCount(const QModelIndex &index = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;

public slots:
    QString get_file_name(int index) const;
};

#endif // FILESDATAMODELBASE_H
