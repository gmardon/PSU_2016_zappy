#include "gamemap.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include "iostream"

GameMap::GameMap()
{
    this->width = 0;
    this->height = 0;
    this->hide();
}

GameMap::~GameMap()
{

}

void GameMap::init(int width, int height)
{
    this->height = height;
    this->width = width;
    for (int y = 0 ; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            this->cells.push_back(new MapCell(x, y));
            this->cells.back()->_grass = (qrand() % 4) + 1;
        }
    }
    this->show();
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
    return QRectF(0.0, 0.0, width * 128, height * 37);
}

void GameMap::paint( QPainter* painter,
                     const QStyleOptionGraphicsItem*,
                     QWidget* )
{
    QPixmap grass1(":/images/grass_1.png");
    QPixmap grass2(":/images/grass_2.png");
    QPixmap grass3(":/images/grass_3.png");
    QPixmap grass4(":/images/grass_4.png");
    QPixmap monkey_N(":/images/monkey_N.png");
    QPixmap monkey_E(":/images/monkey_E.png");
    QPixmap monkey_S(":/images/monkey_S.png");
    QPixmap monkey_O(":/images/monkey_O.png");
    QPixmap perl(":/images/perl.png");
    QPixmap berry(":/images/berry.png");
    QPixmap crystal(":/images/crystal.png");
    QPixmap diamond(":/images/diamond.png");
    QPixmap blue_potion(":/images/blue_potion.png");
    QPixmap red_potion(":/images/red_potion.png");
    QPixmap feather(":/images/feather.png");
    for (int y = 0 ; y < height; y++)
    {
        //painter->drawLine(QLine((y % 2 == 0 ? 0 : 43) + 0 * 128, y * 25, (y % 2 == 0 ? 0 : 43) + 10 * 87, y * 25));
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
            painter->drawPixmap((y % 2 == 0 ? 0 : 64) + x * 128, y * 37, grass);
        }
    }

    for (int y = 0 ; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int item_id = 0;
            MapCell *cell = getCell(x, y);
            int cell_x = ((y % 2 == 0 ? 0 : 64) + x * 128);
            int cell_y = (y * 37);
            if (cell->getFood() != 0)
            {
                item_id++;
                painter->drawPixmap(cell_x + (item_id * 16) + (item_id % 2 == 0 ? 16 : 0), cell_y  + (item_id * 16) - (item_id % 2 == 0 ? 32 : 0), berry);
            }
            if (cell->getLinemate() != 0)
            {
                item_id++;
                painter->drawPixmap(cell_x + (item_id * 16) + (item_id % 2 == 0 ? 16 : 0), cell_y + (item_id * 16) - (item_id % 2 == 0 ? 32 : 0), perl);
            }
            if (cell->getDeraumere() != 0)
            {
                item_id++;
                painter->drawPixmap(cell_x + (item_id * 16) + (item_id % 2 == 0 ? 16 : 0), cell_y + (item_id * 16) - (item_id % 2 == 0 ? 32 : 0), crystal);
            }
            if (cell->getSibur() != 0)
            {
                item_id++;
                painter->drawPixmap(cell_x + (item_id * 16) + 5 + (item_id % 2 == 0 ? 16 : 0), cell_y + (item_id * 16) + 5 - (item_id % 2 == 0 ? 32 : 0) - (item_id == 3 ? 16 : 0), diamond);
            }
            if (cell->getMendiane() != 0)
            {
                item_id++;
                painter->drawPixmap(cell_x + (item_id * 16) + (item_id % 2 == 0 ? 16 : 0), cell_y + (item_id * 16) - (item_id % 2 == 0 ? 32 : 0) - (item_id == 3 ? 16 : 0), blue_potion);
            }
            if (cell->getPhiras() != 0)
            {
                item_id++;
                painter->drawPixmap(cell_x + (item_id * 16) +  (item_id % 2 == 0 ? 16 : 0), cell_y + (item_id * 16) - 5 - (item_id % 2 == 0 ? 32 : 0) - (item_id == 3 ? 10 : 0), red_potion);
            }
            if (cell->getThystame() != 0)
            {
                item_id++;
                painter->drawPixmap(cell_x + (item_id * 16) + 5 + (item_id % 2 == 0 ? 16 : 0) - (item_id == 3 ? 8 : 0), cell_y + (item_id * 14) - (item_id % 2 == 0 ? 32 : 0) - (item_id == 3 ? 8 : 0), feather);
            }
        }
    }

    for (auto player = players.begin(); player != players.end(); player++)
    {
        int x = (*player)->getX();
        int y = (*player)->getY();
        int cell_x = ((y % 2 == 0 ? 0 : 64) + x * 128);
        int cell_y = (y * 37);

        QPixmap player_image;
        switch((*player)->getDirection())
        {
        case 1:
            player_image = monkey_N;
            break;
        case 2:
            player_image = monkey_E;
            break;
        case 3:
            player_image = monkey_S;
            break;
        case 4:
            player_image = monkey_O;
            break;
        }
        painter->drawPixmap(cell_x - 160, cell_y - 57, player_image);
        painter->drawText(cell_x - 145, cell_y - 65, QString::fromStdString((*player)->getTeam()));
        painter->drawText(cell_x - 145, cell_y - 85, QString::fromStdString("Level: " + std::to_string((*player)->getLevel())));
    }
}

std::vector<MapCell*> *GameMap::getCells()
{
    return &(this->cells);
}


std::vector<std::string> *GameMap::getTeams()
{
    return &(this->teams);
}

Player *GameMap::getPlayer(int id)
{
    int index = 0;
    for (auto player = players.begin(); player != players.end();player++)
    {
        if ((*player)->getId() == id)
        {
            return players.at(index);
        }
        index++;
    }
}

void GameMap::removePlayer(int id)
{
    for (auto player = players.begin(); player != players.end();player++)
    {
        if ((*player)->getId() == id)
        {
            players.erase(player);
        }
    }
}

void GameMap::addPlayer(Player *player)
{
    this->players.push_back(player);
}

void GameMap::addTeam(std::string team)
{
    this->teams.push_back(team);
}
