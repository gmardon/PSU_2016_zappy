#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "gamemap.h"
#include "authenticationdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene();
    //GameMap *map = new GameMap(5, 5);
    QPixmap image(":/images/grass.png");

    QGraphicsPixmapItem *enemyItem = scene->addPixmap(image);
    enemyItem->setPos(50, 50);

    scene->addItem(map);

    view->setScene(scene);
   // view->show();

    AuthenticationDialog *dialog = new AuthenticationDialog();
    dialog->show();

    return a.exec();
}
