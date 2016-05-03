#include "header/adminlogin.h"
#include "ui_adminlogin.h"

AdminLogin::AdminLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogin)
{
    this->setWindowTitle("Admin Login");
    ui->setupUi(this);

}

AdminLogin::~AdminLogin()
{
    delete ui;
}

void AdminLogin::on_pushButton_ok_clicked()
{
    if(ui->lineEdit_passwordForm->text() == "password")
    {
        qDebug() << "hey";
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
