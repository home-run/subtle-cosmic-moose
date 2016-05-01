#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QDialog>
#include "database.h"
#include <QMessageBox>
#include <QFile>

namespace Ui {
class AdminLogin;
}

class AdminLogin : public QDialog
{
    Q_OBJECT

public:
    explicit AdminLogin(QWidget *parent = 0);
    ~AdminLogin();

private slots:
    // checks to see if the password is correct
    void on_pushButton_ok_clicked();
    // closes the window
    void on_pushButton_cancel_clicked();

    void on_lineEdit_passwordForm_returnPressed();

signals:
    void adminStatusChanged(bool status);

private:
    Ui::AdminLogin *ui;
    Database*  _database;
};

#endif // ADMINLOGIN_H
