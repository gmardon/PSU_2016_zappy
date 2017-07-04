#include "gameend.h"

GameEnd::GameEnd()
{
    this->hide();
}

GameEnd::~GameEnd()
{

}

QRectF GameEnd::boundingRect() const
{
    return QRectF(0.0, 0.0, 512.0, 512.0);
}

void GameEnd::run(std::string winningTeam)
{
    this->winningTeam = winningTeam;
    this->show();
}


void GameEnd::paint( QPainter* painter,
                     const QStyleOptionGraphicsItem*,
                     QWidget* )
{
    painter->setFont({"Helvetica", 20});
    QPixmap end(":/images/end.png");
    //QPixmap restart(":/images/btn_restart.png");
    painter->drawPixmap(this->scene()->width() / 2 - 160, this->scene()->height() / 2 - 100, end);
    painter->drawText(this->scene()->width() / 2 - 60, this->scene()->height() / 2 - 65, QString::fromStdString(this->winningTeam + " win !"));

    //painter->drawPixmap(this->scene()->width() / 2 - 80, this->scene()->height() / 2 + 20, restart);
}
