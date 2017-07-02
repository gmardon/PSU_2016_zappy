#include "clientsocket.h"

ClientSocket::ClientSocket()
{
    QObject::connect(&socket, SIGNAL(connected()),this, SLOT(_connected()));
    QObject::connect(&socket, SIGNAL(readyRead()), this, SLOT(read()));
    QObject::connect(&socket, SIGNAL(disconnected()), this, SLOT(_disconnected()));
}
void ClientSocket::connect(std::string address, int port)
{
    socket.connectToHost(QString::fromStdString(address), port);
}
void ClientSocket::write(std::string data)
{
    QTextStream stream(&socket);
    std::cout << "> " << data;
    stream << QString::fromStdString(data);
}

void ClientSocket::_connected()
{
    emit onConnected();
}

void ClientSocket::_disconnected()
{
    emit onDisconnected();
}

void ClientSocket::read()
{
    QString data;
    while(socket.canReadLine())
    {
        data = socket.readLine();
        emit onMessage(data.toStdString());
    }
}
