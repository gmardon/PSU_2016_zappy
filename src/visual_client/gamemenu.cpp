#include "gamemenu.h"

GameMenu::GameMenu()
{

}


GameMenu::~GameMenu()
{

}

QRectF GameMenu::boundingRect() const
{
    return QRectF(0.0, 0.0, 124, 124);
}

void GameMenu::paint( QPainter* painter,
                     const QStyleOptionGraphicsItem*,
                     QWidget* )
{

}
