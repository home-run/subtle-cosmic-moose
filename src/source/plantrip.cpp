#include "header/plantrip.h"
#include "ui_plantrip.h"

PlanTrip::PlanTrip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlanTrip)
{
    ui->setupUi(this);
}

PlanTrip::~PlanTrip()
{
    delete ui;
}
