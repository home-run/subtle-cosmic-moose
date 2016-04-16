#include "editstadiuminfo.h"
#include "ui_editstadiuminfo.h"

EditStadiumInfo::EditStadiumInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditStadiumInfo)
{
    ui->setupUi(this);
}

EditStadiumInfo::~EditStadiumInfo()
{
    delete ui;
}
