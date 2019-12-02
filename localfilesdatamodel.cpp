#include "localfilesdatamodel.h"

LocalFilesDataModel::LocalFilesDataModel(QObject* parent)
    :FilesDataModelBase (parent)
{
    retrieve_user_files();
}

void LocalFilesDataModel::delete_file(int index)
{
    if(index < 0 || index >= files.size()) return;
    FileManager file_manager;
    QFile file(file_manager.get_file_path(files[index].first));
    if(file.remove()) {
        beginRemoveRows(QModelIndex(), index, index);
        files.removeAt(index);
        endRemoveRows();
    }
}


void LocalFilesDataModel::retrieve_user_files()
{
    FileManager file_manager;
    auto user_files = file_manager.retrieve_user_files();
    for(int i = 0; i < user_files.size(); ++i)
        files.push_back({{user_files[i].baseName()},{user_files[i].lastModified().toString("dd.MM.yy hh:mm:ss")}});
}













