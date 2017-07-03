#include "authenticationdialog.h"
#include "ui_authenticationdialog.h"
#include "zappy.h"

AuthenticationDialog::AuthenticationDialog(Zappy *zappy, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthenticationDialog)
{
    ui->setupUi(this);
    this->zappy = zappy;
}

AuthenticationDialog::~AuthenticationDialog()
{
    delete ui;
}

void AuthenticationDialog::on_connect_clicked()
{
    zappy->connect(ui->server_host->text().toStdString(), ui->server_port->text().toInt());
    this->close();
}
