#include "header/plantrip.h"
#include "ui_plantrip.h"

PlanTrip::PlanTrip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlanTrip)
{
    ui->setupUi(this);
}

PlanTrip::~PlanTrip()
{
    delete ui;
}

/**
 * @brief PlanTrip::propagateStadiumTable
 * This method takes a database object that is sqlite database and retrieve the
 * stadiums / teams within the database. It will only propagate the stadium name
 * and team name into the table view.
 * @param db
 * database object that inherits the qt sqlite database.
 */
void PlanTrip::propagateStadiumTable(Database *db)
{
    QSqlTableModel* model = new QSqlTableModel(this,db->database());

    model->setTable("stadiums");
    model->select();
    model->setHeaderData(1, Qt::Horizontal, tr("Team Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Stadium Name"));

    if(ui->planTrip_tableView_stadiums == NULL)
    {
        ui->planTrip_tableView_stadiums = new QTableView;
    }
    ui->planTrip_tableView_stadiums->setModel(model);
    ui->planTrip_tableView_stadiums->hideColumn(0);
    ui->planTrip_tableView_stadiums->hideColumn(3);
    ui->planTrip_tableView_stadiums->hideColumn(4);
    ui->planTrip_tableView_stadiums->hideColumn(5);
    ui->planTrip_tableView_stadiums->hideColumn(6);
    ui->planTrip_tableView_stadiums->hideColumn(7);
    ui->planTrip_tableView_stadiums->hideColumn(8);
    ui->planTrip_tableView_stadiums->hideColumn(9);
    ui->planTrip_tableView_stadiums->resizeColumnsToContents();
    ui->planTrip_tableView_stadiums->show();

}
