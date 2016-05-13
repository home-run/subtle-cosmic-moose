#include "header/plantrip.h"
#include "ui_plantrip.h"
#include <QDebug>

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

void PlanTrip::propagateStadiumList(QSqlQuery query)
{
    QStringList stadiumNames;
    while(query.next()){
        stadiumNames.append( query.record().field("name").value().toString() );
    }

    ui->planTrip_stadiums_tableWidget->addItems(stadiumNames);

    emit hideNextButton(true);

}

void PlanTrip::on_planTrip_stadiums_tableWidget_doubleClicked(const QModelIndex &index)
{
    ui->planTrip_stadiumsChosen_tableWidget->addItem(ui->planTrip_stadiums_tableWidget->takeItem(index.row()));
}

void PlanTrip::on_planTrip_stadiumsChosen_tableWidget_doubleClicked(const QModelIndex &index)
{
    ui->planTrip_stadiums_tableWidget->addItem(ui->planTrip_stadiumsChosen_tableWidget->takeItem(index.row()));
}

void PlanTrip::on_planTrip_toolButton_moveUp_clicked()
{
    int currentIndex = ui->planTrip_stadiumsChosen_tableWidget->currentRow();
    QListWidgetItem *currentItem = ui->planTrip_stadiumsChosen_tableWidget->takeItem(currentIndex);
    ui->planTrip_stadiumsChosen_tableWidget->insertItem(currentIndex-1, currentItem);
    ui->planTrip_stadiumsChosen_tableWidget->setCurrentRow(currentIndex-1);
}

void PlanTrip::on_planTrip_toolButton_moveDown_clicked()
{
    int currentIndex = ui->planTrip_stadiumsChosen_tableWidget->currentRow();
    QListWidgetItem *currentItem = ui->planTrip_stadiumsChosen_tableWidget->takeItem(currentIndex);
    ui->planTrip_stadiumsChosen_tableWidget->insertItem(currentIndex+1, currentItem);
    ui->planTrip_stadiumsChosen_tableWidget->setCurrentRow(currentIndex+1);
}

void PlanTrip::on_planTrip_pushButton_dreamVacation_clicked()
{
    int size = ui->planTrip_stadiumsChosen_tableWidget->count();
    QStringList stadiumNames;
    for(int i = 0; i < size; i++){
        stadiumNames.append(ui->planTrip_stadiumsChosen_tableWidget->item(i)->text());
    }

    emit giveStadiumList(stadiumNames);
    emit clickNext();
}
