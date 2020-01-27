#include "client.h"

const QString Client::host_name = "supernovaexplosion.ddns.net";
//const QString Client::host_name = "10.123.12.130";

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

bool Client::sing_in(const QString &user_name, const QString &user_password)
{
    if(!socket.isValid()) return false;
    if(socket.write(json_helper.create_json(JSonHelper::Token::sing_in, user_name, user_password)) == -1) {
        return false;
    }
    else {
        return true;
    }
}

bool Client::sing_up(const QString &user_name, const QString &user_password)
{
    if(!socket.isValid()) return false;
    if(socket.write(json_helper.create_json(JSonHelper::Token::sing_up, user_name, user_password)) == -1) {
        return false;
    }
    else {
        return true;
    }
}

bool Client::upload_file(const QString &file_name)
{
    if(!socket.isValid()) return false;
    this->file_name = file_name;
    Settings settings;
    FileManager file_manager;
    QFile file(file_manager.get_file_path(file_name));
    if(socket.write(json_helper.create_json(JSonHelper::Token::upload_file, settings.get_user_name(), "", file_name, file.size())) == -1) {
        return false;
    }
    else {
        return true;
    }
}

bool Client::download_file(const QString &file_name)
{
    if(!socket.isValid()) return false;
    this->file_name = file_name;
    Settings settings;
    if(socket.write(json_helper.create_json(JSonHelper::Token::download_file, settings.get_user_name(), "", file_name)) == -1) {
        return false;
    }
    else {
        return true;
    }
}

bool Client::delete_file(const QString &file_name)
{
    if(!socket.isValid()) return false;
    Settings settings;
    if(socket.write(json_helper.create_json(JSonHelper::Token::delete_file, settings.get_user_name(), "", file_name))) {
        return false;
    }
    else {
        return true;
    }
}

void Client::process_data()
{
    if(token == JSonHelper::Token::ready_receive_file) {
        if(data.size() == file_size) {
            save_file();
            return;
        }
        return;
    }
    if(json_helper.is_json(data)) {
        token = json_helper.get_token();
        file_size = json_helper.get_file_size();
        data.clear();
        action();
    } // else resume receive data...
}

void Client::action()
{
    qDebug() << "Token = " << static_cast<int>(token);
    switch (token)
    {
    case JSonHelper::Token::success_sing_in: {
        emit success_sing_in();
        break;
    }
    case JSonHelper::Token::unsuccess_sing_in: {
        emit unsuccess_sing_in();
        break;
    }
    case JSonHelper::Token::success_sing_up: {
        emit success_sing_up();
    break;
    }
    case JSonHelper::Token::unsuccess_sing_up: {
        emit unsuccess_sing_up();
        break;
    }
    case JSonHelper::Token::ready_upload_file: {
        send_file();
        break;
    }
    case JSonHelper::Token::internal_server_error: {
        emit internal_server_error();
        break;
    }
    case JSonHelper::Token::list_of_files: {
        emit list_of_files(json_helper.get_files_str());
        emit connected_to_server();
        json_helper.clear();
        break;
    }
    case JSonHelper::Token::ready_send_file: {
        ready_receive_file_response();
        break;
    }
    }
}

void Client::send_file()
{
    FileManager file_manager;
    QFile file(file_manager.get_file_path(file_name));
    if(file.open(QIODevice::ReadOnly)) {
        socket.write(file.readAll());
        file.close();
    }
}

void Client::get_list_of_files()
{
    Settings settings;
    socket.write(json_helper.create_json(JSonHelper::Token::list_of_files, settings.get_user_name()));
}

void Client::ready_receive_file_response()
{
    token = JSonHelper::Token::ready_receive_file;
    Settings settings;
    socket.write(json_helper.create_json(JSonHelper::Token::ready_receive_file, settings.get_user_name(), "", file_name));
}

void Client::save_file()
{
    FileManager file_manager;
    QFile file(file_manager.get_file_path(file_name));
    if(file.open(QIODevice::WriteOnly)) {
        file.write(data);
        file.close();
        emit success_downloading();
    }
    else {
        emit unsuccess_downloading();
    }
    token = static_cast<JSonHelper::Token>(99999);
    data.clear();
}


void Client::connected()
{
    qDebug() << this << " connected";
    Settings settings;
    if(!settings.get_user_name().isEmpty()) {
        get_list_of_files();
    }
    else {
        emit connected_to_server();
    }
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
    process_data();
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
        emit server_refused_connection();
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
}

void Client::connect_to_host()
{
    socket.connectToHost(server_ip, server_port);
}










