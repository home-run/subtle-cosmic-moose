#include "header/stadiumtablemodel.h"

StadiumTableModel::StadiumTableModel(QObject *parent, Database *db) : QSqlTableModel(parent, *db)
{
    Initialize();
}

void StadiumTableModel::Initialize()
{
    this->setTable("stadiums");
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->setHeaderData(NAME, Qt::Horizontal, tr("Stadium Name"), 0);
    this->setHeaderData(TEAM, Qt::Horizontal, tr("Home Team"), 0);
    this->setHeaderData(ADDRESS, Qt::Horizontal, tr("Address"), 0);
    this->setHeaderData(PHONE, Qt::Horizontal, tr("Box Office Phone #"), 0);
    this->setHeaderData(DATE, Qt::Horizontal, tr("Opening Date"), 0);
    this->setHeaderData(CAPACITY, Qt::Horizontal, tr("Seating Capacity"), 0);
    this->setHeaderData(TURF, Qt::Horizontal, tr("Turf Type"), 0);
    this->setHeaderData(REVENUE, Qt::Horizontal, tr("Revenue"), 0);
    this->setHeaderData(LEAGUE, Qt::Horizontal, tr("League"), 0);
}
