#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>
#include <QDebug>
#include "filemanager.h"

class Settings: public QObject
{
    Q_OBJECT
    FileManager file_manager;
    QString user_name;
    QString user_password;

private:
    void load_user_settings();

public:
    explicit Settings(QObject* parent = nullptr);

public slots:
    void save_user_settings(const QString& user_name, const QString& user_password);
    void delete_user_settings_and_files();
    QString get_user_name() const;
    QString get_user_password() const;
};

#endif // SETTINGS_H
