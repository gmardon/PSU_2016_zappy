#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <QGraphicsItem>
#include <QGraphicsScene>

class GameMenu : public QGraphicsItem
{
public:
    GameMenu();
    ~GameMenu();

    QRectF boundingRect() const;
    void paint( QPainter *painter,
                const QStyleOptionGraphicsItem *option,
                QWidget *widget);
};


#endif // GAMEMENU_H
