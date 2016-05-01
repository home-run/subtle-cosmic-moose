#include "header/addsouvenir.h"
#include "ui_addsouvenir.h"

addsouvenir::addsouvenir(QWidget *parent, Database *db) :
    QDialog(parent),
    ui(new Ui::addsouvenir)
{
    ui->setupUi(this);
    this->db = db;
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

}
