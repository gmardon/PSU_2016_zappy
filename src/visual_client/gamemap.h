#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "mapcell.h"
#include "player.h"

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
    Player *getPlayer(int id);
    void removePlayer(int id);
    void addPlayer(Player *player);

private:
    int height;
    int width;
    std::vector<MapCell*> cells;
    std::vector<Player*> players;
};


#endif // GAMEMAP_H
