#include "header/stadiumdetails.h"
#include "ui_stadiumdetails.h"

StadiumDetails::StadiumDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StadiumDetails)
{
    ui->setupUi(this);
    toggleAdminFunctions(false);
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

    // stretch last field to the end
    ui->stadiumDetails_tableView_stadiumInfo->horizontalHeader()->setStretchLastSection(true);
}

/**
 * @brief StadiumDetails::initializeSouvenirView
 * Initialize settings for souvenir table view.
 */
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
 * @brief StadiumDetails::toggleAdminFunctions
 * Hide/unhide and enable/disable all buttons and features for
 * admin use only.
 * @param isAdmin true if user is admin
 */
void StadiumDetails::toggleAdminFunctions(bool isAdmin)
{
    // Hide/unhide and enable/disable submit changes button
    ui->stadiumDetails_admin_submitChanges->setEnabled(isAdmin);
    ui->stadiumDetails_admin_submitChanges->setVisible(isAdmin);

    // Hide/unhide and enable/disable add souvenir button
    ui->stadiumDetails_admin_addSouvenir->setEnabled(isAdmin);
    ui->stadiumDetails_admin_addSouvenir->setVisible(isAdmin);

    // Hide/unhide and enable/disable remove souvenir button
    ui->stadiumDetails_admin_removeSouvenir->setEnabled(isAdmin);
    ui->stadiumDetails_admin_removeSouvenir->setVisible(isAdmin);

    if(isAdmin)
    {
        // make tables editable
        ui->stadiumDetails_tableView_stadiumInfo->setEditTriggers(QTableView::DoubleClicked);
        ui->stadiumDetails_tableView_souvenirs->setEditTriggers(QTableView::DoubleClicked);

        // set it to submit changes on manual submit
        this->stadiumModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        this->souvenirModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    }
    else
    {
        // make tables uneditable
        ui->stadiumDetails_tableView_stadiumInfo->setEditTriggers(QTableView::NoEditTriggers);
        ui->stadiumDetails_tableView_souvenirs->setEditTriggers(QTableView::NoEditTriggers);
    }
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
 * @brief StadiumDetails::initializeSouvenirTable
 * Initializes the souvenirTable using the model emitted from mainWindow
 * @param souvenirModel The model emitted from mainWindow
 */
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

/**
 * @brief StadiumDetails::on_stadiumDetails_tableView_stadiumInfo_clicked
 * Updates the souvenir table with the appropriate souvenir list
 * when the user clicks a row in the stadium table.
 * @param index the index of the selected row
 */
void StadiumDetails::on_stadiumDetails_tableView_stadiumInfo_clicked(const QModelIndex &index)
{
    int stadium = stadiumModel->record(index.row()).value("id").toInt();
    // Initialize the model to the selected stadium.
    souvenirModel->Initialize(stadium);
    // Reinitialize the souvenir view.
    initializeSouvenirView();
}

/**
 * @brief StadiumDetails::on_stadiumDetails_tableView_stadiumInfo_activated
 * Updates the souvenir table with the appropriate souvenir list
 * when the user presses enter after selecting a row in the stadium table.
 * @param index the index of the selected row
 */
void StadiumDetails::on_stadiumDetails_tableView_stadiumInfo_activated(const QModelIndex &index)
{
    int stadium = stadiumModel->record(index.row()).value("id").toInt();
    // Initialize the model to the selected stadium.
    souvenirModel->Initialize(stadium);
    // Reinitialize the souvenir view.
    initializeSouvenirView();
}

/**
 * @brief StadiumDetails::on_stadiumDetails_admin_submitChanges_clicked
 * Submit all changes to the database permanently.
 */
void StadiumDetails::on_stadiumDetails_admin_submitChanges_clicked()
{
    // Pop up a dialog to verify that admin wants to actually submit changes
    QMessageBox *p = new QMessageBox(this);
    p->setWindowTitle("Submit Changes");
    p->setText("Submit all changes to the database");
    p->setInformativeText("Are you sure?");
    p->setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    p->setDefaultButton(QMessageBox::Cancel);
    int decision = p->exec();

    // If the user hits OK
    if(decision == QMessageBox::Ok)
    {
        // submit changes to the DB
        stadiumModel->submitAll();
        souvenirModel->submitAll();

        // re-propagate tables
        stadiumModel->select();
        souvenirModel->select();
    }
}
