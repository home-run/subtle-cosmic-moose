#include "header/purchasewindow.h"
#include "ui_purchasewindow.h"
#include <QSpinBox>

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
 * @brief PurchaseWindow::getPurchases
 * Retrieve a list of purchaseInfo structs containing all of the data
 * in the souvenir purchase list (cart).
 * contains:
 *  - stadium name
 *  - item name
 *  - item price
 *  - item quantity
 *
 * @return purchases a list of purchaseInfo structs
 */
QList<PurchaseWindow::purchaseInfo> PurchaseWindow::getPurchases()
{
    QList<purchaseInfo> purchases; // list of purchaseInfo structs
    purchaseInfo row; // struct representing one row in the cart
    QModelIndex stadiumNameIndex; // index of the stadium name
    QModelIndex itemNameIndex; // index of the item name
    QModelIndex priceIndex; // index of the price
    QModelIndex quantityBoxIndex; // index of the quantity spinBox
    QString stadiumName; // stadium name
    QString itemName; // item name
    QSpinBox *box; // quantity spinBox
    double price; // price
    int quantity; // quantity value

    int rows = ui->purchaseWindow_tableWidget_shoppingCart->rowCount();

    // Loop through the entire cart adding data to structs, and adding the structs to a list.
    for(int i = 0; i < rows; i++)
    {
        stadiumNameIndex = ui->purchaseWindow_tableWidget_shoppingCart->model()->index(i, 0);
        itemNameIndex    = ui->purchaseWindow_tableWidget_shoppingCart->model()->index(i, 1);
        priceIndex       = ui->purchaseWindow_tableWidget_shoppingCart->model()->index(i, 2);

        // set spinBox pointer to point at the spinBox in the tableWidget
        box              = static_cast<QSpinBox*>(ui->purchaseWindow_tableWidget_shoppingCart->cellWidget(i, 3));

        stadiumName = ui->purchaseWindow_tableWidget_shoppingCart->model()->data(stadiumNameIndex).toString();
        itemName    = ui->purchaseWindow_tableWidget_shoppingCart->model()->data(itemNameIndex).toString();
        price       = ui->purchaseWindow_tableWidget_shoppingCart->model()->data(priceIndex).toDouble();
        quantity    = box->value();

        row.stadiumName = stadiumName;
        row.itemName    = itemName;
        row.itemPrice   = price;
        row.quantity    = quantity;

        purchases.append(row);
    }

    return purchases;
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
    // Set index of currently selected row in the souvenir List
    int selectedRow = index.row();

    // Set QModelIndex of the name of the souvenir selected
    QModelIndex souvenirName_index  = ui->purchaseWindow_tableView_souvenirList->model()->index(selectedRow, 1);

    // Set QModelIndex of the price of the souvenir clicked
    QModelIndex souvenirPrice_index  = ui->purchaseWindow_tableView_souvenirList->model()->index(selectedRow, 2);

    // Set name of the currently selected souvenir
    QString souvenirName = ui->purchaseWindow_tableView_souvenirList->model()->data(souvenirName_index).toString();

    // Set price of the currently selected souvenir
    double price = ui->purchaseWindow_tableView_souvenirList->model()->data(souvenirPrice_index).toDouble();

    // Create text items to insert into cart row
    QTableWidgetItem *stadiumName = new QTableWidgetItem( ui->purchaseWindow_comboBox_selectStadium->currentText() );
    QTableWidgetItem *itemName  = new QTableWidgetItem( souvenirName );
    QTableWidgetItem *priceItem = new QTableWidgetItem( QString::number(price) );

    // Create quantity spinBox to insert into cart row
    QSpinBox *quantity = new QSpinBox( ui->purchaseWindow_tableWidget_shoppingCart );

    // Set max and min quantities for quantity spinBox
    quantity->setRange(1, 99);

    // Get current row count (the index at which to insert the new row)
    int rowCount = ui->purchaseWindow_tableWidget_shoppingCart->rowCount();

    // Insert the new row into the cart
    ui->purchaseWindow_tableWidget_shoppingCart->insertRow(rowCount);
    ui->purchaseWindow_tableWidget_shoppingCart->setItem(rowCount, 0, stadiumName);
    ui->purchaseWindow_tableWidget_shoppingCart->setItem(rowCount, 1, itemName);
    ui->purchaseWindow_tableWidget_shoppingCart->setItem(rowCount, 2, priceItem);
    ui->purchaseWindow_tableWidget_shoppingCart->setCellWidget(rowCount, 3, quantity);
}

void PurchaseWindow::initializeCartWidget()
{    
    QStringList headerData;
    headerData.append("Stadium");
    headerData.append("Item");
    headerData.append("Price");
    headerData.append("Quantity");

    // clear shopping cart
    ui->purchaseWindow_tableWidget_shoppingCart->clear();
    ui->purchaseWindow_tableWidget_shoppingCart->clearContents();
    while(ui->purchaseWindow_tableWidget_shoppingCart->rowCount() > 0){
        ui->purchaseWindow_tableWidget_shoppingCart->removeRow(0);
    }

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

void PurchaseWindow::on_purchaseWindow_tableWidget_shoppingCart_doubleClicked(const QModelIndex &index)
{
    ui->purchaseWindow_tableWidget_shoppingCart->removeRow(index.row());
}

void PurchaseWindow::on_toolButton_clicked()
{
    if(ui->purchaseWindow_tableView_souvenirList->currentIndex().row() > -1){
    on_purchaseWindow_tableView_souvenirList_doubleClicked(ui->purchaseWindow_tableView_souvenirList->currentIndex());
    }
}

void PurchaseWindow::on_toolButton_2_clicked()
{
    if(ui->purchaseWindow_tableWidget_shoppingCart->currentIndex().row() > -1){
    ui->purchaseWindow_tableWidget_shoppingCart->removeRow(ui->purchaseWindow_tableWidget_shoppingCart->currentIndex().row());
    }
}
