#include "header/stadiumdetails.h"
#include "ui_stadiumdetails.h"

StadiumDetails::StadiumDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StadiumDetails)
{
    ui->setupUi(this);
}

/**
 * @brief StadiumDetails::initializeStadiumView
 * Initialize settings for stadium table view.
 */
void StadiumDetails::initializeStadiumView()
{
    // hide vertical header
    ui->stadiumDetails_tableView_stadiumInfo->verticalHeader()->setVisible(false);

    // turn alternating row colors on
    ui->stadiumDetails_tableView_stadiumInfo->setAlternatingRowColors(true);

    // make table uneditable
    ui->stadiumDetails_tableView_stadiumInfo->setEditTriggers(QTableView::NoEditTriggers);

    // turn word-wrap on... this might do what we want it to do.. I DON'T KNOW
    ui->stadiumDetails_tableView_stadiumInfo->setWordWrap(true);

    // make it so selection selects each row
    ui->stadiumDetails_tableView_stadiumInfo->setSelectionBehavior(QAbstractItemView::SelectRows);

    // enable sorting
    ui->stadiumDetails_tableView_stadiumInfo->setSortingEnabled(true);

    // resize columns to contents
    ui->stadiumDetails_tableView_stadiumInfo->resizeColumnsToContents();
}

StadiumDetails::~StadiumDetails()
{
    delete ui;
}

void StadiumDetails::initializeStadiumTable(StadiumTableModel *stadiumModel)
{
    ui->stadiumDetails_tableView_stadiumInfo->setModel(stadiumModel);
    initializeStadiumView();
}
