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
    QString file_name;
    qint64 file_size = 0;
    JSonHelper json_helper;
    JSonHelper::Token token;

private:
    void process_data();
    void action();
    void send_file();
    void get_list_of_files();
    void ready_receive_file_response();
    void save_file();

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

signals:
    void finished_searching_host();
    void connected_to_server();
    void server_refused_connection();

    void success_sing_in();
    void unsuccess_sing_in();
    void success_sing_up();
    void unsuccess_sing_up();
    void internal_server_error();

    void list_of_files(const QString& list);
    void success_downloading();
    void unsuccess_downloading();

public slots:
    bool sing_in(const QString& user_name, const QString& user_password);
    bool sing_up(const QString& user_name, const QString& user_password);
    bool upload_file(const QString& file_name);
    bool download_file(const QString& file_name);
    bool delete_file(const QString& file_name);
};

#endif // CLIENT_H
