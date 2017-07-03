#include "player.h"

Player::Player(int id, int x, int y, int direction, int level, std::string team)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->direction = direction;
    this->level = level;
    this->team = team;
}

void Player::setPosition(int x, int y, int direction)
{
    this->x = x;
    this->y = y;
    this->direction = direction;
}
