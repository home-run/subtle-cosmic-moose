#include "header/purchasewindow.h"
#include "ui_purchasewindow.h"

PurchaseWindow::PurchaseWindow(QWidget *parent, Database *db) :
    QWidget(parent),
    ui(new Ui::PurchaseWindow)
{
    ui->setupUi(this);

    // Set local db pointer to the database.
    this->db = db;

    // Instantiate souvenirModel
    souvenirModel = new SouvenirTableModel(this, db);

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

/**
 * @brief PurchaseWindow::propagateStadiumList
 * Propagate the comboBox with the list of selected stadiums to visit.
 * @param stadiums QStringList of stadium names
 */
void PurchaseWindow::propagateStadiumList(QStringList stadiums)
{
    // clear in case user has exited out and come back
    ui->purchaseWindow_comboBox_selectStadium->clear();

    // propagate comboBox with stadium list
    ui->purchaseWindow_comboBox_selectStadium->addItems(stadiums);

    initializeCartWidget();
}

/**
 * @brief PurchaseWindow::on_purchaseWindow_comboBox_selectStadium_currentIndexChanged
 * Propagate the souvenirs table with the souvenirs of the currently selected stadium when
 * a user changes the selected stadium in the combo box.
 * @param arg1 the name of the stadium that is currently selected
 */
void PurchaseWindow::on_purchaseWindow_comboBox_selectStadium_currentIndexChanged(const QString &arg1)
{
    // Get the name of the first Stadium in the list
    QString currentStadium = ui->purchaseWindow_comboBox_selectStadium->currentText();
    qDebug() << "current stadium selection: " + currentStadium;

    // Get the ID of that stadium
    int stadiumID = db->GetStadiumID(arg1);

    // Initialize souvenirModel to the souvenirs of that stadium.
    souvenirModel->Initialize(stadiumID);

    // Set model to the initialized souvenirModel
    ui->purchaseWindow_tableView_souvenirList->setModel(souvenirModel);

    // Sets all table settings to make the table look pretty.
    initializeSouvenirView();
}

/**
 * @brief PurchaseWindow::on_purchaseWindow_tableView_souvenirList_doubleClicked
 * Add a souvenir to the shopping cart.
 * @param index the index of the souvenir to add
 */
void PurchaseWindow::on_purchaseWindow_tableView_souvenirList_doubleClicked(const QModelIndex &index)
{
    int selectedRow = index.row();
    QModelIndex souvenirName_index  = ui->purchaseWindow_tableView_souvenirList->model()->index(selectedRow, 1);
    QModelIndex souvenirPrice_index  = ui->purchaseWindow_tableView_souvenirList->model()->index(selectedRow, 2);
    QString souvenirName = ui->purchaseWindow_tableView_souvenirList->model()->data(souvenirName_index).toString();
    double price = ui->purchaseWindow_tableView_souvenirList->model()->data(souvenirPrice_index).toDouble();

    QTableWidgetItem *stadiumName = new QTableWidgetItem("testStadium");
    QTableWidgetItem *itemName  = new QTableWidgetItem(souvenirName);
    QTableWidgetItem *priceItem = new QTableWidgetItem(price);
    QTableWidgetItem *quantity = new QTableWidgetItem("0");

    int rowCount = ui->purchaseWindow_tableWidget_shoppingCart->rowCount();

    ui->purchaseWindow_tableWidget_shoppingCart->insertRow(rowCount);
    ui->purchaseWindow_tableWidget_shoppingCart->setItem(rowCount - 1, 0, stadiumName);
    ui->purchaseWindow_tableWidget_shoppingCart->setItem(rowCount - 1, 1, itemName);
    ui->purchaseWindow_tableWidget_shoppingCart->setItem(rowCount - 1, 2, priceItem);
    ui->purchaseWindow_tableWidget_shoppingCart->setItem(rowCount - 1, 3, quantity);
}

void PurchaseWindow::initializeCartWidget()
{
    QTableWidgetItem *item = new QTableWidgetItem();

    QStringList headerData;
    headerData.append("Stadium");
    headerData.append("Item");
    headerData.append("Price");
    headerData.append("Quantity");

    // set number of columns to size of headerData stringList
    ui->purchaseWindow_tableWidget_shoppingCart->setColumnCount(headerData.size());

    // set horizontal header labels
    ui->purchaseWindow_tableWidget_shoppingCart->setHorizontalHeaderLabels(headerData);

    // hide vertical header
    ui->purchaseWindow_tableWidget_shoppingCart->verticalHeader()->setVisible(false);

    // turn alternating row colors on
    ui->purchaseWindow_tableWidget_shoppingCart->setAlternatingRowColors(true);

    // make table uneditable
    ui->purchaseWindow_tableWidget_shoppingCart->setEditTriggers(QTableView::NoEditTriggers);

    // turn word-wrap on... this might do what we want it to do.. I DON'T KNOW
    ui->purchaseWindow_tableWidget_shoppingCart->setWordWrap(true);

    // make it so selection selects each row
    ui->purchaseWindow_tableWidget_shoppingCart->setSelectionBehavior(QAbstractItemView::SelectRows);

    // make it so only one stadium row can be selected at a time
    ui->purchaseWindow_tableWidget_shoppingCart->setSelectionMode(QAbstractItemView::SingleSelection);

    // enable sorting
    ui->purchaseWindow_tableWidget_shoppingCart->setSortingEnabled(true);

    // set headers as not resizable.
    ui->purchaseWindow_tableWidget_shoppingCart->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // stretch the last section of header
    ui->purchaseWindow_tableWidget_shoppingCart->horizontalHeader()->setStretchLastSection(true);

}
