#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "gamemap.h"

class GameMenu : public QGraphicsItem
{
public:
    GameMenu();
    ~GameMenu();

    void init(GameMap *map);

    QRectF boundingRect() const;
    void paint( QPainter *painter,
                const QStyleOptionGraphicsItem *option,
                QWidget *widget);
private:
    GameMap *map;
};


#endif // GAMEMENU_H
