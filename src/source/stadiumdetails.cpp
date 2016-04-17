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

/**
 * @brief StadiumDetails::initializeStadiumTable
 * @param stadiumModel The model to initialize the table to.
 */
void StadiumDetails::initializeStadiumTable(StadiumTableModel *stadiumModel)
{
    // Set this class's stadiumModel attribute to the one that's
    // passed in so we can use it later.
    this->stadiumModel = stadiumModel;

    // Set the model of the stadiumInfo table
    ui->stadiumDetails_tableView_stadiumInfo->setModel(this->stadiumModel);

    // Initialize table settings.
    initializeStadiumView();
}

/**
 * @brief StadiumDetails::on_stadiumDetails_league_comboBox_currentIndexChanged
 * Changes the table filter based on which league is selected. Will filter stadiums
 * by league.
 * @param index current index of the comboBox
 */
void StadiumDetails::on_stadiumDetails_league_comboBox_currentIndexChanged(int index)
{
    enum Leagues
    {
        ALL,
        AMERICAN,
        NATIONAL,
        MAJOR
    };

    switch(index)
    {
    case ALL:
        stadiumModel->setFilter("");
        break;
    case AMERICAN:
        stadiumModel->setFilter("league = 'American'");
        break;
    case NATIONAL:
        stadiumModel->setFilter("league = 'National'");
        break;
    case MAJOR:
        stadiumModel->setFilter("league = 'Major'");
        break;
    default:
        stadiumModel->setFilter("");
        break;
    }
}
