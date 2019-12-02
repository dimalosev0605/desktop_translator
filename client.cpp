#include "client.h"

const QString Client::host_name = "supernovaexplosion.ddns.net";

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

bool Client::upload_file(const QString &file_name)
{
    if(!socket.isValid()) return false;
    method = JSonHelper::Method::upload_file;
    this->file_name = file_name;
    Settings settings;
    FileManager file_manager;
    QFile file(file_manager.get_file_path(file_name));
    socket.write(json_helper.load_file_json(JSonHelper::Method::upload_file, settings.get_user_name(),
                                            settings.get_user_password(), file_name, file.size()));
    return true;
}

void Client::get_list_of_files()
{
    if(!socket.isValid()) return;
    method = JSonHelper::Method::get_list_of_files;
    Settings settings;
    socket.write(json_helper.create_json(method, settings.get_user_name(), settings.get_user_password()));
}

void Client::sing_in_f(const QString &user_name, const QString &user_password)
{
    if(!socket.isValid()) return;
    method = JSonHelper::Method::sign_in;
    socket.write(json_helper.create_json(method, user_name, user_password));
}

void Client::sing_up_f(const QString &user_name, const QString &user_password)
{
    if(!socket.isValid()) return;
    method = JSonHelper::Method::sign_up;
    socket.write(json_helper.create_json(method, user_name, user_password));
}


void Client::process_data(const QByteArray &data)
{
    if(json_helper.is_json(data))
    {
        action();
    }
}

void Client::process_sign_in()
{
//    if(json_helper.is_json(data))
//    {
//        state = json_helper.get_state();
//        if(state == JSonHelper::State::success_sing_in)
//            emit success_sing_in();
//        else
//            emit unsuccess_sing_in();
//        data.clear();
//    }
    state = json_helper.get_state();
    switch (state) {
    case JSonHelper::State::success_sing_in:
    {
        emit success_sing_in();
        break;
    }
    case JSonHelper::State::unsuccess_sing_in:
    {
        emit unsuccess_sing_in();
        break;
    }
    case JSonHelper::State::internal_server_error:
    {
        emit internal_server_error();
        break;
    }
    }
    data.clear();
}


void Client::process_sign_up()
{
//    if(json_helper.is_json(data))
//    {
//        state = json_helper.get_state();
//        if(state == JSonHelper::State::success_sign_up)
//            emit success_sing_up();
//        else
//            emit unsuccess_sing_up();
//        data.clear();
//    }
    state = json_helper.get_state();
    switch (state) {
    case JSonHelper::State::success_sign_up:
    {
        emit success_sing_up();
        break;
    }
    case JSonHelper::State::unsuccess_sign_up:
    {
        emit unsuccess_sing_up();
        break;
    }
    case JSonHelper::State::internal_server_error:
    {
        emit internal_server_error();
        break;
    }
    }
    data.clear();
}

void Client::process_upload_file()
{
    state = json_helper.get_state();
    switch (state) {
    case JSonHelper::State::ready_upload_file: {
        FileManager file_manager;
        QFile file(file_manager.get_file_path(file_name));
        if(file.open(QIODevice::ReadOnly))
        {
            socket.write(file.readAll());
        }
        file.close();
        data.clear();
        break;
    }
    case JSonHelper::State::success_uploading: {
        data.clear();
        emit success_uploading();
        break;
    }
    }
}

void Client::action()
{
    switch (method){
    case JSonHelper::Method::sign_in:
    {
        process_sign_in();
        break;
    }
    case JSonHelper::Method::sign_up:
    {
        process_sign_up();
        break;
    }
    case JSonHelper::Method::upload_file:
    {
        process_upload_file();
        break;
    }
    case JSonHelper::Method::get_list_of_files: {
        process_get_list_of_files();
        break;
    }
    }
}

void Client::process_get_list_of_files()
{
    auto list = json_helper.get_list_of_files();
    data.clear();
//    emit list_of_files(list);
}


void Client::connected()
{
    qDebug() << this << " connected";
    get_list_of_files();
    emit connected_to_server();
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
    process_data(data);
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
    else {
        qDebug() << "host not found";
    }
}

void Client::connect_to_host()
{
    socket.connectToHost(server_ip, server_port);
}










