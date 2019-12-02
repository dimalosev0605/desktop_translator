#include "remotefilesdatamodel.h"

RemoteFilesDataModel::RemoteFilesDataModel(QObject* parent)
    :FilesDataModelBase (parent)
{

}

void RemoteFilesDataModel::receive_list_of_files(const QStringList &list)
{
    for(int i = 0; i < list.size(); ++i)
        qDebug() << list[i];
}


