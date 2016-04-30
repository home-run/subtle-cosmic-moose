#include "header/purchasewindow.h"
#include "ui_purchasewindow.h"

PurchaseWindow::PurchaseWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PurchaseWindow)
{
    ui->setupUi(this);
}

PurchaseWindow::~PurchaseWindow()
{
    delete ui;
}
