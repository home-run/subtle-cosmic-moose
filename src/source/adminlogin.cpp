#include "adminlogin.h"
#include "ui_adminlogin.h"
#include "database.h"

AdminLogin::AdminLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
    this->setWindowTitle("Admin Login");
}

AdminLogin::~AdminLogin()
{
    delete ui;
}

void AdminLogin::on_pushButton_ok_clicked()
{
    if(ui->lineEdit_passwordForm->text() == "password")
    {
        emit adminStatusChanged(true);

        this->close();
    }
    else if(ui->lineEdit_passwordForm->text().isEmpty())
    {
        ui->label_errorMessage->setText("Please enter a password.");
    }
    else
    {
        ui->label_errorMessage->setText("Invalid Password");
    }
}

void AdminLogin::on_pushButton_cancel_clicked()
{
    QWidget::close();
}

void AdminLogin::on_lineEdit_passwordForm_returnPressed()
{
    ui->pushButton_ok->click();
}
