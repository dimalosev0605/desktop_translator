#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QHostInfo>
#include <QHostAddress>
#include "jsonhelper.h"

class Client: public QObject
{
    Q_OBJECT

    QTcpSocket socket;
    QString server_ip;
    quint16 server_port = 228;
    JSonHelper json_helper;
    QByteArray data;
    JSonHelper::State state;

private:
    void process_answer();

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

public slots:
    void sign_up(const QString& user_name, const QString& user_password);
    void sign_in(const QString& user_name, const QString& user_password);

signals:
    void finished_searching_host();
    void success_sing_up();
    void success_sign_in();
    void sign_up_conflict();
    void unlucky_sing_in();
    void server_error();
};

#endif // CLIENT_H
