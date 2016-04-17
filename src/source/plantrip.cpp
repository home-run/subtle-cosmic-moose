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
    ui->planTrip_tableView_stadiums->show();
}
