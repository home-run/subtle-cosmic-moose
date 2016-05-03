#include "header/addsouvenir.h"
#include "ui_addsouvenir.h"

addsouvenir::addsouvenir(QWidget *parent, Database *db, QString stadiumName) :
    QDialog(parent),
    ui(new Ui::addsouvenir)
{
    ui->setupUi(this);
    this->stadiumName = stadiumName;
    this->db = db;
    this->setWindowTitle("Add Souvenir to " + stadiumName);
}

addsouvenir::~addsouvenir()
{
    delete ui;
}

/**
 * @brief addsouvenir::on_addSouvenir_confirmation_buttonBox_accepted
 * Add a souvenir to the appropriate souvenir table
 */
void addsouvenir::on_addSouvenir_confirmation_buttonBox_accepted()
{
    QString itemName = ui->addSouvenir_souvenirName_lineEdit->text();
    double itemPrice = ui->addSouvenir_price_doubleSpinBox->value();
    if(db->AddSouvenir(stadiumName, itemName, itemPrice)){
        qDebug() << itemName + " was successfully added to " << stadiumName << "\'s souvenir list.";
        emit refreshModels();
    } else {
        qDebug() << "failed to add the souvenir";
    }
}

/**
 * @brief addsouvenir::on_addSouvenir_confirmation_buttonBox_rejected
 * If admin hits cancel, close the window.
 */
void addsouvenir::on_addSouvenir_confirmation_buttonBox_rejected()
{
    this->close();
}
