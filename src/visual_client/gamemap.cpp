#include "gamemap.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include "iostream"

GameMap::GameMap(int height, int width)
{
    this->height = height;
    this->width = width;
}

GameMap::~GameMap()
{

}

QRectF GameMap::boundingRect() const
{
    return QRectF(0.0, 0.0, 512.0, 512.0);
}

void GameMap::paint( QPainter* painter,
                     const QStyleOptionGraphicsItem*,
                     QWidget* )
{
    QPixmap grass1(":/images/grass_1.png");
    QPixmap grass2(":/images/grass_2.png");
    QPixmap monkey_wait(":/images/monkey_wait.png");
    for (int y = 0 ; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            painter->drawPixmap((y % 2 == 0 ? 0 : 43 ) + x * 87, y * 25, grass1);
        }
    }

    for (int y = 0 ; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (x == 4 && y == 10)
            {
                painter->drawPixmap((y % 2 == 0 ? 0 : 43 ) + x * 87, y * 25 + 40, monkey_wait);
            }
        }
    }
}
