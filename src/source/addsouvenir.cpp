#include "header/addsouvenir.h"
#include "ui_addsouvenir.h"

addsouvenir::addsouvenir(QWidget *parent, Database *db) :
    QDialog(parent),
    ui(new Ui::addsouvenir)
{
    ui->setupUi(this);
    this->db = db;
    qDebug() << "got here";
    this->setWindowTitle("Add Souvenir");
    ui->addSouvenir_stadium_comboBox->addItems(db->GetStadiumNames());
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
    QString stadium = ui->addSouvenir_stadium_comboBox->currentText();
    QString itemName = ui->addSouvenir_souvenirName_lineEdit->text();
    double itemPrice = ui->addSouvenir_price_doubleSpinBox->value();
    if(db->AddSouvenir(stadium, itemName, itemPrice)){
        qDebug() << itemName + " was successfully added to " << stadium << "\'s souvenir list.";
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
    close();
}
