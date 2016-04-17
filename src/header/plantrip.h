#ifndef PLANTRIP_H
#define PLANTRIP_H

#include <QWidget>
#include "../header/database.h"
#include <QTableView>
#include <QSqlTableModel>
#include <QCheckBox>

namespace Ui {
class PlanTrip;
}

class PlanTrip : public QWidget
{
    Q_OBJECT

public:
    explicit PlanTrip(QWidget *parent = 0);
    ~PlanTrip();

    /// PropagateStadiumTable
    /// This method will propagate the stadium table view in the plan a trip view
    void propagateStadiumTable(Database* db);

private:
    Ui::PlanTrip *ui;
};

#endif // PLANTRIP_H
