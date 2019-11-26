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
    Q_PROPERTY(bool is_auth READ get_is_auth WRITE set_is_auth NOTIFY is_auth_changed)
    bool is_auth = false;
    FileManager file_manager;
    QString user_name;
    QString user_password;

private:
    void load_user_settings();

public:
    explicit Settings(QObject* parent = nullptr);
    void set_is_auth(bool v);
    bool get_is_auth() const;

public slots:
    void save_user_settings(const QString& user_name, const QString& user_password);
    void delete_user_settings_and_files();
    QString get_user_name() const;
    QString get_user_password() const;

signals:
    void is_auth_changed();
};

#endif // SETTINGS_H
