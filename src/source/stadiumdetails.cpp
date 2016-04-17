#include "header/stadiumdetails.h"
#include "ui_stadiumdetails.h"

StadiumDetails::StadiumDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StadiumDetails)
{
    ui->setupUi(this);
}

StadiumDetails::~StadiumDetails()
{
    delete ui;
}

void StadiumDetails::initializeStadiumTable(StadiumTableModel *stadiumModel)
{
    ui->stadiumDetails_tableView_stadiumInfo->setModel(stadiumModel);
}
