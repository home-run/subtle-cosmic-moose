#include "header/purchasewindow.h"
#include "ui_purchasewindow.h"

PurchaseWindow::PurchaseWindow(QWidget *parent, Database *db) :
    QWidget(parent),
    ui(new Ui::PurchaseWindow)
{
    ui->setupUi(this);

    // Set local db pointer to the database.
    this->db = db;
}

/**
 * @brief StadiumDetails::initializeSouvenirView
 * Initialize settings for souvenir table view.
 */
void PurchaseWindow::initializeSouvenirView()
{
    // hide vertical header
    ui->purchaseWindow_tableView_souvenirList->verticalHeader()->setVisible(false);

    // turn alternating row colors on
    ui->purchaseWindow_tableView_souvenirList->setAlternatingRowColors(true);

    // make table uneditable
    ui->purchaseWindow_tableView_souvenirList->setEditTriggers(QTableView::NoEditTriggers);

    // turn word-wrap on... this might do what we want it to do.. I DON'T KNOW
    ui->purchaseWindow_tableView_souvenirList->setWordWrap(true);

    // make it so selection selects each row
    ui->purchaseWindow_tableView_souvenirList->setSelectionBehavior(QAbstractItemView::SelectRows);

    // make it so only one stadium row can be selected at a time
    ui->purchaseWindow_tableView_souvenirList->setSelectionMode(QAbstractItemView::SingleSelection);

    // enable sorting
    ui->purchaseWindow_tableView_souvenirList->setSortingEnabled(true);

    // set headers as not resizable.
    ui->purchaseWindow_tableView_souvenirList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // hide id column
    ui->purchaseWindow_tableView_souvenirList->setColumnHidden(SouvenirTableModel::STADIUM_ID, true);

    // stretch the last section of header
    ui->purchaseWindow_tableView_souvenirList->horizontalHeader()->setStretchLastSection(true);

}

PurchaseWindow::~PurchaseWindow()
{
    delete ui;
}

void PurchaseWindow::propagateStadiumList(QStringList stadiums)
{
    // clear in case user has exited out and come back
    ui->purchaseWindow_comboBox_selectStadium->clear();

    // propagate comboBox with stadium list
    ui->purchaseWindow_comboBox_selectStadium->addItems(stadiums);

    // Instantiate souvenirModel
    souvenirModel = new SouvenirTableModel(this, db);

    // Get the name of the first Stadium in the list
    QString currentStadium = ui->purchaseWindow_comboBox_selectStadium->currentText();
    qDebug() << currentStadium;

    // Get the ID of that stadium
    int stadiumID = db->GetStadiumID(currentStadium);

    // Initialize souvenirModel to the souvenirs of that stadium.
    souvenirModel->Initialize(stadiumID);

    // Set model to the initialized souvenirModel
    ui->purchaseWindow_tableView_souvenirList->setModel(souvenirModel);

    initializeSouvenirView();
}

void PurchaseWindow::on_purchaseWindow_comboBox_selectStadium_currentIndexChanged(const QString &arg1)
{

}

