#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "mapcell.h"

class GameMap : public QGraphicsItem
{
public:
    GameMap();
    ~GameMap();

    void init(int height, int width);

    QRectF boundingRect() const;
    void paint( QPainter *painter,
                const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    std::vector<MapCell*> *getCells();
    MapCell *getCell(int x, int y);

private:
    int height;
    int width;
    std::vector<MapCell*> cells;
};


#endif // GAMEMAP_H
