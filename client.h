#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QHostInfo>
#include <QHostAddress>
#include "jsonhelper.h"
#include "settings.h"

class Client: public QObject
{
    Q_OBJECT

    static const QString host_name;
    static const qint16 server_port = 228;
    QTcpSocket socket;
    QString server_ip;
    QByteArray data;
    JSonHelper json_helper;
    JSonHelper::Method method;
    JSonHelper::State state;
    QString file_name;

    void process_data(const QByteArray& data);
    void process_sign_in();
    void process_sign_up();
    void process_upload_file();
    void action();
    void process_get_list_of_files();

private slots:
    void connected();
    void disconnected();
    void ready_read();
    void bytes_written(qint64 bytes);
    void stateChanged(QAbstractSocket::SocketState socketState);
    void hostFound();
    void error(QAbstractSocket::SocketError socketError);
    void search_host(const QHostInfo& host_info);
    void connect_to_host();

public:
    explicit Client(QObject* parent = nullptr);
    void get_list_of_files();

public slots:
    void sing_in_f(const QString& user_name, const QString& user_password);
    void sing_up_f(const QString& user_name, const QString& user_password);
    bool upload_file(const QString& file_name);

signals:
    void finished_searching_host();
    void connected_to_server();
    void success_sing_in();
    void unsuccess_sing_in();
    void success_sing_up();
    void unsuccess_sing_up();
    void internal_server_error();
    void success_uploading();
    void list_of_files(const QStringList& list);
};

#endif // CLIENT_H
