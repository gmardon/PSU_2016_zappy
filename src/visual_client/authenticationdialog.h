#ifndef AUTHENTICATIONDIALOG_H
#define AUTHENTICATIONDIALOG_H
#include "zappy.h"
#include <QDialog>

namespace Ui {
class AuthenticationDialog;
}

class AuthenticationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthenticationDialog(Zappy *zappy, QWidget *parent = 0);
    ~AuthenticationDialog();

private slots:
    void on_connect_clicked();

private:
    Ui::AuthenticationDialog *ui;
    Zappy *zappy;
};

#endif // AUTHENTICATIONDIALOG_H
