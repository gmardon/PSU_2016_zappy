#include "zappy.h"

Zappy::Zappy(std::string address, int port)
{
    this->map = new GameMap(20, 10);
    this->socket = new ClientSocket();
    QObject::connect(this->socket, SIGNAL(onConnected()),this, SLOT(handleConnected()));
    QObject::connect(this->socket, SIGNAL(onMessage(std::string)), this, SLOT(handleMessage(std::string)));
    QObject::connect(this->socket, SIGNAL(onDisconnected()), this, SLOT(handleDisconnected()));
    this->socket->connect(address, port);
}

GameMap *Zappy::getMap()
{
    return (this->map);
}

void Zappy::handleConnected()
{

}

void Zappy::handleMessage(std::string message)
{
    std::cout << "< " << message << std::endl;
    if (message == "WELCOME\n")
    {
        this->socket->write("GRAPHIC\n");
        return;
    }
}


void Zappy::handleDisconnected()
{

}
