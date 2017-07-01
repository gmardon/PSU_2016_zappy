#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <QGraphicsItem>
#include <QGraphicsScene>

class GameMap : public QGraphicsItem
{
public:
    GameMap(int height, int width);
    ~GameMap();

    void paint( QPainter *painter,
                const QStyleOptionGraphicsItem *option,
                QWidget *widget);
};


#endif // GAMEMAP_H
