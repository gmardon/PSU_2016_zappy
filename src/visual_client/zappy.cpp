#include "zappy.h"

Zappy::Zappy()
{
    this->map = new GameMap();
    this->menu = new GameMenu();
    this->socket = new ClientSocket();
    QObject::connect(this->socket, SIGNAL(onConnected()),this, SLOT(handleConnected()));
    QObject::connect(this->socket, SIGNAL(onMessage(std::string)), this, SLOT(handleMessage(std::string)));
    QObject::connect(this->socket, SIGNAL(onDisconnected()), this, SLOT(handleDisconnected()));
    this->gameEnded = false;
}

void Zappy::connect(std::string address, int port)
{
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
    std::vector<std::string> query = split(message, " ");
    if (query.at(0) == "WELCOME\n")
    {
        this->socket->write("GRAPHIC\n");
    }
    else if (query.at(0) == "msz")
    {
        int width = atoi(query.at(1).c_str());
        int height = atoi(query.at(2).c_str());
        this->map->init(width, height);
        this->addItem(map);
        this->menu->init(this->map);
        this->addItem(menu);
    }
    else if (query.at(0) == "bct")
    {
        int x = atoi(query.at(1).c_str());
        int y = atoi(query.at(2).c_str());
        int food = atoi(query.at(3).c_str());
        int linemate = atoi(query.at(4).c_str());
        int deraumere = atoi(query.at(5).c_str());
        int sibur = atoi(query.at(6).c_str());
        int mendiane = atoi(query.at(7).c_str());
        int phiras = atoi(query.at(8).c_str());
        int thystame = atoi(query.at(9).c_str());
        MapCell *cell = this->map->getCell(x, y);
        cell->setRessources(food, linemate, deraumere, sibur, mendiane, phiras, thystame);
    }
    else if (query.at(0) == "pnw")
    {
        int id = atoi(query.at(1).c_str());
        int x = atoi(query.at(2).c_str());
        int y = atoi(query.at(3).c_str());
        int direction = atoi(query.at(4).c_str());
        int level = atoi(query.at(5).c_str());
        std::string team = query.at(6);
        Player *player = new Player(id, x, y, direction, level, team);
        map->addPlayer(player);
    }
    else if (query.at(0) == "pex" || query.at(0) == "pdi")
    {
        int id = atoi(query.at(1).c_str());

        map->removePlayer(id);
    }
    else if (query.at(0) == "ppo")
    {
        int id = atoi(query.at(1).c_str());
        int x = atoi(query.at(2).c_str());
        int y = atoi(query.at(3).c_str());
        int direction = atoi(query.at(4).c_str());
        Player *player = map->getPlayer(id);

        player->setPosition(x, y, direction);
    }
    else if (query.at(0) == "plv")
    {
        int id = atoi(query.at(1).c_str());
        int level = atoi(query.at(2).c_str());

        Player *player = map->getPlayer(id);

        player->setLevel(level);
        QSound::play(":/sounds/level_up.wav");
    }
    else if (query.at(0) == "tna")
    {
        std::string team = query.at(1);
        this->map->addTeam(team);
    }
    else if (query.at(0) == "seg")
    {
        std::string team = query.at(1);
        this->endGame(team);
    }
    this->map->update();
    this->menu->update();
}

void Zappy::endGame(std::string winningTeam)
{
    this->removeItem(map);
    this->removeItem(menu);
    this->update();
    this->gameEnded = true;
    this->end = new GameEnd();
    this->addItem(this->end);
    this->end->run(winningTeam);
}

void Zappy::handleDisconnected()
{

}
