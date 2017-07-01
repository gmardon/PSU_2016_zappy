#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "clientsocket.h"
#include "gamemap.h"

class Zappy : public QObject
{
Q_OBJECT
public:
    Zappy(std::string address, int port);
    GameMap *getMap();

private:
    ClientSocket *socket;
    GameMap *map;

private slots :
    void handleDisconnected();
    void handleConnected();
    void handleMessage(std::string);
};

#endif // GAME_H
