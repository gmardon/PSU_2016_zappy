#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

class Player
{
public:
    Player(int id, int x, int y, int direction, int level, std::string team);
    ~Player();

    void setPosition(int x, int y, int direction);

private:
    int id;
    int direction; // N:1, E:2, S:3, O:3
    int x;
    int y;
    int level;
    std::string team;

public:
    int getId() { return this->id; }
    int getX() { return this->x; }
    int getY() { return this->y; }
    int getDirection() { return this->direction; }
    std::string getTeam() { return this->team; }

};

#endif // PLAYER_H
