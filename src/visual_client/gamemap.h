#ifndef GAMEMAP_H
#define GAMEMAP_H


class GameMap : public QGraphicsItem
{
public:
    GameMap();
    ~GameMap();

    void paint( QPainter *painter,
                const QStyleOptionGraphicsItem *option,
                QWidget *widget);
};


#endif // GAMEMAP_H
