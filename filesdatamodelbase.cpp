#include "filesdatamodelbase.h"

FilesDataModelBase::FilesDataModelBase(QObject *parent)
    : QAbstractListModel (parent)
{
    m_roleNames[static_cast<int>(RolesNames::file_name)] = "file_name";
    m_roleNames[static_cast<int>(RolesNames::modified_date)] = "modified_date";
}

QHash<int, QByteArray> FilesDataModelBase::roleNames() const
{
    return m_roleNames;
}


int FilesDataModelBase::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return files.size();
}

QVariant FilesDataModelBase::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= files.size()) return QVariant();

    switch (role) {
    case static_cast<int>(RolesNames::file_name):
        return files[row].first;

    case static_cast<int>(RolesNames::modified_date):
        return files[row].second;

    }

    return QVariant();
}

QString FilesDataModelBase::get_file_name(int index) const
{
    if(index < 0 || index >= files.size()) return QString();
    return files[index].first;
}





