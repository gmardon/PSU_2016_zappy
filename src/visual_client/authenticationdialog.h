#ifndef AUTHENTICATIONDIALOG_H
#define AUTHENTICATIONDIALOG_H

#include <QDialog>

namespace Ui {
class AuthenticationDialog;
}

class AuthenticationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthenticationDialog(QWidget *parent = 0);
    ~AuthenticationDialog();

private:
    Ui::AuthenticationDialog *ui;
};

#endif // AUTHENTICATIONDIALOG_H
