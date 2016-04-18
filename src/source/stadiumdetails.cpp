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

    // make it so only one stadium row can be selected at a time
    ui->stadiumDetails_tableView_stadiumInfo->setSelectionMode(QAbstractItemView::SingleSelection);

    // enable sorting
    ui->stadiumDetails_tableView_stadiumInfo->setSortingEnabled(true);

    // set headers as not resizable.
    ui->stadiumDetails_tableView_stadiumInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // hide id column
    ui->stadiumDetails_tableView_stadiumInfo->setColumnHidden(StadiumTableModel::ID, true);
}

void StadiumDetails::initializeSouvenirView()
{
    // hide vertical header
    ui->stadiumDetails_tableView_souvenirs->verticalHeader()->setVisible(false);

    // turn alternating row colors on
    ui->stadiumDetails_tableView_souvenirs->setAlternatingRowColors(true);

    // make table uneditable
    ui->stadiumDetails_tableView_souvenirs->setEditTriggers(QTableView::NoEditTriggers);

    // turn word-wrap on... this might do what we want it to do.. I DON'T KNOW
    ui->stadiumDetails_tableView_souvenirs->setWordWrap(true);

    // make it so selection selects each row
    ui->stadiumDetails_tableView_souvenirs->setSelectionBehavior(QAbstractItemView::SelectRows);

    // make it so only one stadium row can be selected at a time
    ui->stadiumDetails_tableView_souvenirs->setSelectionMode(QAbstractItemView::SingleSelection);

    // enable sorting
    ui->stadiumDetails_tableView_souvenirs->setSortingEnabled(true);

    // set headers as not resizable.
    ui->stadiumDetails_tableView_souvenirs->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // hide id column
    ui->stadiumDetails_tableView_souvenirs->setColumnHidden(SouvenirTableModel::STADIUM_ID, true);

    // stretch the last section of header
    ui->stadiumDetails_tableView_souvenirs->horizontalHeader()->setStretchLastSection(true);
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

void StadiumDetails::initializeSouvenirTable(SouvenirTableModel *souvenirModel)
{
    // Set this class's souvenirModel attribute to the one that's
    // passed in so we can use it later.
    this->souvenirModel = souvenirModel;

    // Set the model of the stadiumInfo table
    ui->stadiumDetails_tableView_souvenirs->setModel(this->souvenirModel);

    // Initialize table settings.
    initializeSouvenirView();
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
        ALL_LEAGUES,
        AMERICAN,
        NATIONAL,
        MAJOR
    };

    enum Surfaces
    {
        ALL_SURFACES,
        GRASS,
        ASTRO
    };

    int currentSurface = ui->stadiumDetails_surface_comboBox->currentIndex();

    switch(currentSurface){
    case ALL_SURFACES:
        switch(index)
        {
        case ALL_LEAGUES:
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
        break;
    case GRASS:
        switch(index)
        {
        case ALL_LEAGUES:
            stadiumModel->setFilter("turf = 'Grass'");
            break;
        case AMERICAN:
            stadiumModel->setFilter("league = 'American' and turf = 'Grass'");
            break;
        case NATIONAL:
            stadiumModel->setFilter("league = 'National' and turf = 'Grass'");
            break;
        case MAJOR:
            stadiumModel->setFilter("league = 'Major' and turf = 'Grass'");
            break;
        default:
            stadiumModel->setFilter("turf = 'Grass'");
            break;
        }
        break;
    case ASTRO:
        switch(index)
        {
        case ALL_LEAGUES:
            stadiumModel->setFilter("turf = 'Astro Turf'");
            break;
        case AMERICAN:
            stadiumModel->setFilter("league = 'American' and turf = 'Astro Turf'");
            break;
        case NATIONAL:
            stadiumModel->setFilter("league = 'National' and turf = 'Astro Turf'");
            break;
        case MAJOR:
            stadiumModel->setFilter("league = 'Major' and turf = 'Astro Turf'");
            break;
        default:
            stadiumModel->setFilter("turf = 'Astro Turf'");
            break;
        }
        break;
    }
}

/**
 * @brief StadiumDetails::on_stadiumDetails_surface_comboBox_currentIndexChanged
 * This function will switch the table filter depending on which surface is selected.
 * It checks to see which leagues are selected and constructs an appropriate filter.
 * @param index The surface that is currently selected
 */
void StadiumDetails::on_stadiumDetails_surface_comboBox_currentIndexChanged(int index)
{
    enum Surfaces
    {
        ALL_SURFACES,
        GRASS,
        ASTRO
    };

    enum Leagues
    {
        ALL_LEAGUES,
        AMERICAN,
        NATIONAL,
        MAJOR
    };

    // Get current league filter selection
    int currentLeague = ui->stadiumDetails_league_comboBox->currentIndex();

    switch(currentLeague)
    {
    case ALL_LEAGUES:
        switch(index)
        {
        case ALL_SURFACES:
            stadiumModel->setFilter("");
            break;
        case GRASS:
            stadiumModel->setFilter("turf = 'Grass'");
            break;
        case ASTRO:
            stadiumModel->setFilter("turf = 'Astro Turf'");
            break;
        default:
            stadiumModel->setFilter("");
            break;
        } // end switch
        break;
    case AMERICAN:
        switch(index)
        {
        case ALL_SURFACES:
            stadiumModel->setFilter("league = 'American'");
            break;
        case GRASS:
            stadiumModel->setFilter("league = 'American' and turf = 'Grass'");
            break;
        case ASTRO:
            stadiumModel->setFilter("league = 'American' and turf = 'Astro Turf'");
            break;
        default:
            stadiumModel->setFilter("league = 'American'");
            break;
        } // end switch
        break;
    case NATIONAL:
        switch(index)
        {
        case ALL_SURFACES:
            stadiumModel->setFilter("league = 'National'");
            break;
        case GRASS:
            stadiumModel->setFilter("league = 'National' and turf = 'Grass'");
            break;
        case ASTRO:
            stadiumModel->setFilter("league = 'National' and turf = 'Astro Turf'");
            break;
        default:
            stadiumModel->setFilter("league = 'National'");
            break;
        } // end switch
        break;
    case MAJOR:
        switch(index)
        {
        case ALL_SURFACES:
            stadiumModel->setFilter("league = 'Major'");
            break;
        case GRASS:
            stadiumModel->setFilter("league = 'Major' and turf = 'Grass'");
            break;
        case ASTRO:
            stadiumModel->setFilter("league = 'Major' and turf = 'Astro Turf'");
            break;
        default:
            stadiumModel->setFilter("league = 'Major'");
            break;
        } // end switch
        break;
    } // end switch
}

void StadiumDetails::on_stadiumDetails_tableView_stadiumInfo_clicked(const QModelIndex &index)
{
    int stadium = stadiumModel->record(index.row()).value("id").toInt();
    souvenirModel->Initialize(stadium);
}
