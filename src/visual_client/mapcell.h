#ifndef MAPCELL_H
#define MAPCELL_H

class MapCell
{
public:
    MapCell(int x, int y);
    int getX();
    int getY();
    void setRessources(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);
    int _grass;
private:
    int x;
    int y;
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;

public:
    int getFood() { return this->food; }
    void setFood(int food) { this->food = food; }
};

#endif // MAPCELL_H
