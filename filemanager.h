#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QDir>
#include <QCoreApplication>

class FileManager
{
public:
    explicit FileManager();
    void create_user_files_dir();
    void create_user_settings_dir();
    QString get_file_path(const QString& file_name);
    QString get_user_files_dir();
    QString get_auth_file_path();
};

#endif // FILEMANAGER_H
