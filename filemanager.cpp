#include "filemanager.h"

const QString user_files_dir = "user_files";
const QString user_settings_dir = "user_settings";
const QString abk_extension = ".abk";
const QString auth_file = "auth_file";

FileManager::FileManager()
{
    create_user_files_dir();
    create_user_settings_dir();
}

void FileManager::create_user_files_dir()
{
    QDir dir(QCoreApplication::applicationDirPath());
    if(!dir.exists(user_files_dir))
    {
        dir.mkdir(user_files_dir);
    }
}

void FileManager::create_user_settings_dir()
{
    QDir dir(QCoreApplication::applicationDirPath());
    if(!dir.exists(user_settings_dir))
    {
        dir.mkdir(user_settings_dir);
    }
}

QString FileManager::get_file_path(const QString &file_name)
{
    return QCoreApplication::applicationDirPath() + '/' + user_files_dir + '/' + file_name + abk_extension;
}

QString FileManager::get_user_files_dir()
{
    return QCoreApplication::applicationDirPath() + '/' + user_files_dir;
}

QString FileManager::get_auth_file_path()
{
    return QCoreApplication::applicationDirPath() + '/' + user_settings_dir + '/' + auth_file + abk_extension;
}










