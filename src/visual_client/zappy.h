#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "clientsocket.h"
#include "gamemap.h"
#include "utils.h"
#include "player.h"
#include <QGraphicsItem>
#include "gamemenu.h"
#include <QSound>
#include "gameend.h"

class Zappy : public QGraphicsScene
{
Q_OBJECT
public:
    Zappy();
    void connect(std::string address, int port);
    GameMap *getMap();

private:
    ClientSocket *socket;
    GameMap *map;
    GameMenu *menu;
    GameEnd *end;
    bool gameEnded;

    void endGame(std::string winningTeam);

private slots :
    void handleDisconnected();
    void handleConnected();
    void handleMessage(std::string);
};

#endif // GAME_H
