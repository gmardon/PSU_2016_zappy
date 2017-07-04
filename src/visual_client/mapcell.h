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
    int getLinemate() { return this->linemate; }
    void setLinemate(int linemane) { this->linemate = linemane; }
    int getDeraumere() { return this->deraumere; }
    void setDeraumere(int deraumere) { this->deraumere = deraumere; }
    int getSibur() { return this->sibur; }
    void setSibur(int sibur) { this->sibur = sibur; }
    int getMendiane() { return this->mendiane; }
    void setMendiane(int mendiane) { this->mendiane = mendiane; }
    int getPhiras() { return this->phiras; }
    void setPhiras(int phiras) { this->phiras = phiras; }
    int getThystame() { return this->thystame; }
    void setThystame(int thystame) { this->thystame = thystame; }
};

#endif // MAPCELL_H
