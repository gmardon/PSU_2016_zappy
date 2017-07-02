#include "mapcell.h"

MapCell::MapCell(int x, int y)
{
    this->x = x;
    this->y = y;
    this->food = 0;
    this->linemate = 0;
    this->deraumere = 0;
    this->sibur = 0;
    this->mendiane = 0;
    this->phiras = 0;
    this->thystame = 0;
}

void MapCell::setRessources(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
{
    this->food = food;
    this->linemate = linemate;
    this->deraumere = deraumere;
    this->sibur = sibur;
    this->mendiane = mendiane;
    this->phiras = phiras;
    this->thystame = thystame;
}


int MapCell::getX()
{
    return this->x;
}

int MapCell::getY()
{
    return this->y;
}
