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
    view->showMaximized();

    Zappy *zappy = new Zappy();
    //zappy->connect("127.0.0.1", 4242);
    AuthenticationDialog *dialog = new AuthenticationDialog(zappy);
    dialog->show();

    view->setScene(zappy);
    view->show();




    return a.exec();
}
