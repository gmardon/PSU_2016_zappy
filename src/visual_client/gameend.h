#ifndef GAMEEND_H
#define GAMEEND_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QSound>
#include <QPainter>
#include "iostream"

class GameEnd : public QGraphicsItem
{
public:
    GameEnd();
    ~GameEnd();

    QRectF boundingRect() const;
    void paint( QPainter *painter,
                const QStyleOptionGraphicsItem *option,
                QWidget *widget);



    void run(std::string winningTeam);
private:
    std::string winningTeam;
};

#endif // GAMEEND_H
