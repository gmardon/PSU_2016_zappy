#ifndef MAPCELL_H
#define MAPCELL_H

class MapCell
{
public:
    MapCell(int x, int y);
    int getX();
    int getY();

private:
    int x;
    int y;
};

#endif // MAPCELL_H
