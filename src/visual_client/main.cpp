#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "gamemap.h"
#include "authenticationdialog.h"
#include "zappy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Zappy - Visual client");
    QGraphicsView *view = new QGraphicsView();

    //AuthenticationDialog *dialog = new AuthenticationDialog();
    //dialog->show();
    Zappy *zappy = new Zappy("localhost", 4242);

    //QPixmap image(":/images/grass.png");

   // QGraphicsPixmapItem *enemyItem = scene->addPixmap(image);
   // enemyItem->setPos(50, 50);





    view->setScene(zappy);
    view->show();




    return a.exec();
}
