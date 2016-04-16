#include "header/tripsummary.h"
#include "ui_tripsummary.h"

TripSummary::TripSummary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TripSummary)
{
    ui->setupUi(this);
}

TripSummary::~TripSummary()
{
    delete ui;
}

/**
 * @brief TripSummary::populateTripPath
 * Method will populate the trip path list with given data.
 */
void TripSummary::populateTripPath() // TODO: PASS IN DATA - VALUES INTO METHOD
{
    QStringList tripPathStringList;
    QString itemToAppend;


    for(int i = 0; i < 7; i++)
    {
        itemToAppend = "From City1 -> Destination City2 : Distance [1234]";

        tripPathStringList.append(itemToAppend);
    }

    for(int j = 0; j < tripPathStringList.count();j++)
    {
        ui->tripSummary_listWidget_tripPath->addItem(tripPathStringList.at(j));
    }
}

void TripSummary::clearData()
{
    ui->tripSummary_listWidget_tripPath->clear();
    ui->tripSummary_tableWidget_Purchases->clear();
}


void TripSummary::on_tripSummary_pushButton_finishTripSummary_clicked()
{
    emit(finishTrip(true));
}
