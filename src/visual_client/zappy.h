#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "clientsocket.h"
#include "gamemap.h"
#include "utils.h"
#include "player.h"
#include <QGraphicsItem>
#include "gamemenu.h"
#include <QMediaPlayer>

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
    QMediaPlayer *sound;

private slots :
    void handleDisconnected();
    void handleConnected();
    void handleMessage(std::string);
};

#endif // GAME_H
