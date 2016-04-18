#include "header/souvenirtablemodel.h"

SouvenirTableModel::SouvenirTableModel(QObject *parent, Database *db) : QSqlTableModel(parent, *db)
{
    Initialize();
}

SouvenirTableModel::SouvenirTableModel(QObject *parent, Database *db, int stadiumId) : QSqlTableModel(parent, *db)
{
    Initialize(stadiumId);
}

void SouvenirTableModel::Initialize(int stadiumId)
{
    // set which SQL table to display
    this->setTable("souvenirs");

    // make table only push changes to DB on manual submit
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // set horizontal header titles
    this->setHeaderData(NAME, Qt::Horizontal, tr("Item Name"), 0);
    this->setHeaderData(PRICE, Qt::Horizontal, tr("Item Price"), 0);

    this->setFilter("stadium_id = " + QString::number(stadiumId));

    // propagate model
    this->select();

}
