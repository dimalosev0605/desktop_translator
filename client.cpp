#include "client.h"

const QString host_name = "supernovaexplosion.ddns.net";

const QString success_sign_up = "success sign up";
const QString sign_up_conflict = "sign up conflict";

Client::Client(QObject* parent)
    :QObject (parent)
{

    connect(&socket, &QTcpSocket::stateChanged, this, &Client::stateChanged);
    connect(&socket, &QTcpSocket::hostFound, this, &Client::hostFound);
    connect(&socket, &QTcpSocket::connected, this, &Client::connected);
    connect(&socket, &QTcpSocket::readyRead, this, &Client::ready_read);
    connect(&socket, &QTcpSocket::bytesWritten, this, &Client::bytes_written);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(&socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &Client::error);
    connect(this, &Client::finished_searching_host, this, &Client::connect_to_host);

    QHostInfo::lookupHost(host_name, this, &Client::search_host);
}

void Client::process_answer()
{
    switch(state)
    {
    case JSonHelper::State::sign_up_conflict:
    {
        qDebug() << "sign up conflict";
        emit this->sign_up_conflict();
        break;
    }
    case JSonHelper::State::success_sing_up:
    {
        qDebug() << "sign up success";
        emit this->success_sing_up();
        break;
    }
    case JSonHelper::State::server_error:
    {
        qDebug() << "server error";
        emit this->server_error();
        break;
    }
    case JSonHelper::State::success_sing_in:
    {
        qDebug() << "Success sign in";
        emit this->success_sign_in();
        break;
    }
    case JSonHelper::State::unlucky_sing_in:
    {
        qDebug() << "Unlucky sign in";
        emit this->unlucky_sing_in();
        break;
    }
    }
}

void Client::connected()
{
    qDebug() << this << " connected";
}

void Client::disconnected()
{
    qDebug() << this << " disconnected";
}

void Client::ready_read()
{
    qDebug() << this << " ready read";
    qint64 bytes_available = socket.bytesAvailable();
    data += socket.read(bytes_available);
    if(json_helper.is_json_obj(data))
    {
        state = json_helper.get_state();
        data.clear();
        process_answer();
    }
    else
    {
    }
}

void Client::bytes_written(qint64 bytes)
{
    qDebug() << this << " bytes written " << bytes << " bytes";
}

void Client::stateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << this << " state changed to " << socketState;
    switch (socketState) {
    case QAbstractSocket::SocketState::HostLookupState:
    {
        break;
    }
    case QAbstractSocket::SocketState::ConnectedState:
    {
        break;
    }
    case QAbstractSocket::SocketState::ConnectingState:
    {
        break;
    }
    case QAbstractSocket::SocketState::UnconnectedState:
    {
        break;
    }
    case QAbstractSocket::SocketState::BoundState:
    {
        break;
    }
    case QAbstractSocket::SocketState::ClosingState:
    {
        break;
    }
    }
}

void Client::hostFound()
{
    qDebug() << this << " host found";
}

void Client::error(QAbstractSocket::SocketError socketError)
{
    qDebug() << this << " error " << socketError;
    switch (socketError) {
    case QAbstractSocket::SocketError::ConnectionRefusedError:
    {
        break;
    }
    }
}

void Client::search_host(const QHostInfo& host_info)
{
    auto server_ips = host_info.addresses();
    if(!server_ips.isEmpty()) {
        server_ip = server_ips.first().toString();
        qDebug() << "server_ip = " << server_ip;
        emit finished_searching_host();
    }
    else
    {
        qDebug() << "host not found";
    }
}

void Client::connect_to_host()
{
    socket.connectToHost(server_ip, server_port);
}

void Client::sign_up(const QString& user_name, const QString& user_password)
{
    socket.write(json_helper.create_sing_in_up_doc(user_name, user_password, JSonHelper::Method::sign_up));
}

void Client::sign_in(const QString& user_name, const QString& user_password)
{
    socket.write(json_helper.create_sing_in_up_doc(user_name, user_password, JSonHelper::Method::sign_in));
}











