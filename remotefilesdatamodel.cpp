#include "remotefilesdatamodel.h"

RemoteFilesDataModel::RemoteFilesDataModel(QObject* parent)
    :FilesDataModelBase (parent)
{
}

void RemoteFilesDataModel::receive_list_of_files(const QString &list)
{
    if(!files.isEmpty()) {
        beginRemoveRows(QModelIndex(), 0, files.size() - 1);
        files.clear();
        endRemoveRows();
    }
    if(list.isEmpty()) return;
    auto pairs = list.split('#', QString::SkipEmptyParts);
    beginInsertRows(QModelIndex(), 0, pairs.size() / 2 - 1);
    for(int i = 0; i < pairs.size(); i+= 2) {
        files.push_back({{pairs[i]},{pairs[i + 1]}});
    }
    endInsertRows();
}



