#include "localfilesdatamodel.h"

LocalFilesDataModel::LocalFilesDataModel(QObject* parent)
    :FilesDataModelBase (parent)
{
    retrieve_user_files();
}

void LocalFilesDataModel::delete_file(int index)
{
    if(index < 0 || index >= files.size()) return;
    if(file_manager.delete_file(files[index].first))
    {
        beginRemoveRows(QModelIndex(), index, index);
        files.removeAt(index);
        endRemoveRows();
    }
}

void LocalFilesDataModel::retrieve_user_files()
{
    auto user_files = file_manager.retrieve_user_files();
    for(int i = 0; i < user_files.size(); ++i)
        files.push_back({{user_files[i].baseName()},{user_files[i].lastModified().toString("dd.MM.yy hh:mm:ss")}});
}













