#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <QGraphicsItem>
#include <QGraphicsScene>

class GameMap : public QGraphicsItem
{
public:
    GameMap(int height, int width);
    ~GameMap();

    QRectF boundingRect() const;
    void paint( QPainter *painter,
                const QStyleOptionGraphicsItem *option,
                QWidget *widget);

private:
    int height;
    int width;
};


#endif // GAMEMAP_H
