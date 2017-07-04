#include "gamemenu.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>

GameMenu::GameMenu()
{
    this->hide();
}

void GameMenu::init(GameMap *map)
{
    this->map = map;
    this->show();
}

GameMenu::~GameMenu()
{

}

QRectF GameMenu::boundingRect() const
{
    return QRectF(0.0, 0.0, 800, 800);
}

void GameMenu::paint( QPainter* painter,
                      const QStyleOptionGraphicsItem*,
                      QWidget* )
{
    painter->setFont({"Helvetica", 20});
    QPixmap menu_bottom(":/images/menu_bottom.png");

    painter->drawPixmap(painter->window().width() / 2 - 750 , painter->window().height() - 500, menu_bottom);

    QPixmap food(":/images/berry.png");
    int total_food = 0;
    QPixmap linemate(":/images/perl.png");
    int total_linemate = 0;
    QPixmap deraumere(":/images/crystal.png");
    int total_deraumere = 0;
    QPixmap sibur(":/images/diamond.png");
    int total_sibur = 0;
    QPixmap mendiane(":/images/blue_potion.png");
    int total_mendiane = 0;
    QPixmap phiras(":/images/red_potion.png");
    int total_phiras = 0;
    QPixmap thystame(":/images/feather.png");
    int total_thystame = 0;

    for (auto cell = map->getCells()->begin(); cell != map->getCells()->end(); cell++)
    {
        total_food += (*cell)->getFood();
        total_linemate += (*cell)->getLinemate();
        total_deraumere += (*cell)->getDeraumere();
        total_sibur += (*cell)->getSibur();
        total_mendiane += (*cell)->getMendiane();
        total_phiras += (*cell)->getPhiras();
        total_thystame += (*cell)->getThystame();
    }

    int box_x = painter->window().width() / 2 - 650;
    int box_y = painter->window().height() - 400;

    painter->drawPixmap(box_x - 35, box_y - 25, food);
    painter->drawText(box_x, box_y, QString::fromStdString(std::to_string(total_food) + " foods"));

    painter->drawPixmap(box_x - 35, box_y - 25 + 40, linemate);
    painter->drawText(box_x, box_y + 40, QString::fromStdString(std::to_string(total_linemate) + " linemates"));

    painter->drawPixmap(box_x - 35, box_y - 25 + 80, deraumere);
    painter->drawText(box_x, box_y + 80, QString::fromStdString(std::to_string(total_deraumere) + " deraumeres"));

    painter->drawPixmap(box_x - 35, box_y - 25 + 120, sibur);
    painter->drawText(box_x, box_y + 120, QString::fromStdString(std::to_string(total_sibur) + " siburs"));

    painter->drawPixmap(box_x - 35, box_y - 25 + 160, mendiane);
    painter->drawText(box_x, box_y + 160, QString::fromStdString(std::to_string(total_mendiane) + " mendianes"));

    painter->drawPixmap(box_x - 35, box_y - 25 + 200, phiras);
    painter->drawText(box_x, box_y + 200, QString::fromStdString(std::to_string(total_phiras) + " phiras"));

    painter->drawPixmap(box_x - 35, box_y - 25 + 240, thystame);
    painter->drawText(box_x, box_y + 240, QString::fromStdString(std::to_string(total_thystame) + " thystame"));

    int index = 0;
    for (auto team = map->getTeams()->begin(); team != map->getTeams()->end();team++)
    {
        painter->drawText(box_x + 550, box_y + (30 * index), QString::fromStdString(*team));
        index++;
    }
}
