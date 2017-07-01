#include "gamemap.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include "iostream"

GameMap::GameMap()
{
    this->width = 10;
    this->height = 20;
}

GameMap::~GameMap()
{

}

void GameMap::init(int width, int height)
{
    this->height = height;
    this->width = width;
    //this->cells = std::array<MapCell>();
    for (int y = 0 ; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            this->cells.push_back(new MapCell(x, y));
            this->cells.back()->_grass = (qrand() % 4) + 1;
        }
    }

}

MapCell *GameMap::getCell(int x, int y)
{
    for (auto iter = this->cells.begin(); iter != this->cells.end(); iter++)
    {
        if ((*iter)->getX() == x && (*iter)->getY() == y)
            return (*iter);
    }
    return (NULL);
}

QRectF GameMap::boundingRect() const
{
    return QRectF(0.0, 0.0, width * 90, height * 25);
}

void GameMap::paint( QPainter* painter,
                     const QStyleOptionGraphicsItem*,
                     QWidget* )
{
    QPixmap grass1(":/images/grass_1.png");
    QPixmap grass2(":/images/grass_2.png");
    QPixmap grass3(":/images/grass_3.png");
    QPixmap grass4(":/images/grass_4.png");
    QPixmap monkey_wait(":/images/monkey_wait.png");
    QPixmap banana_alert(":/images/banana_alert.png");
    for (int y = 0 ; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            MapCell *cell = getCell(x, y);
            QPixmap grass;
            switch(cell->_grass)
            {
            case 1:
                grass = grass1;
                break;
            case 2:
                grass = grass2;
                break;
            case 3:
                grass = grass3;
                break;
            case 4:
                grass = grass4;
                break;
            }

            painter->drawPixmap((y % 2 == 0 ? 0 : 43 ) + x * 87, y * 25, grass);
        }
    }

    for (int y = 0 ; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            MapCell *cell = getCell(x, y);
            if (cell->getFood() > 0)
            {

                painter->drawPixmap((y % 2 == 0 ? 0 : 43 ) + x * 87, y * 25 + 40, banana_alert);
            }
            /*if (x == 4 && y == 10)
            {
                painter->drawPixmap((y % 2 == 0 ? 0 : 43 ) + x * 87, y * 25 + 40, monkey_wait);
            }*/
        }
    }
}

std::vector<MapCell*> *GameMap::getCells()
{
    return &(this->cells);
}
