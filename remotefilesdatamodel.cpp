#include "remotefilesdatamodel.h"

RemoteFilesDataModel::RemoteFilesDataModel(QObject* parent)
    :FilesDataModelBase (parent)
{
}

void RemoteFilesDataModel::receive_list_of_files(const QString& list)
{
    auto l = list.split('#', QString::SkipEmptyParts);
    if(l.isEmpty()) return;
    if(!files.isEmpty())
    {
        beginRemoveRows(QModelIndex(), 0, files.size() - 1);
        files.clear();
        endRemoveRows();
    }
    beginInsertRows(QModelIndex(), 0, l.size() / 2 - 1);
    for(int i = 0; i < l.size() - 1; i += 2) {
        files.push_back({{l[i]},{l[i + 1]}});
    }
    endInsertRows();
    for(int i = 0; i < files.size(); ++i) {
        qDebug() << files[i].first << " " << files[i].second;
    }
}


