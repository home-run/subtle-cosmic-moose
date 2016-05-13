#ifndef PLANTRIP_H
#define PLANTRIP_H

#include <QtSql/QtSql>
#include <QWidget>

namespace Ui {
class PlanTrip;
}

class PlanTrip : public QWidget
{
    Q_OBJECT

public:
    explicit PlanTrip(QWidget *parent = 0);

    ~PlanTrip();

public slots:
    void propagateStadiumList(QSqlQuery query);

private slots:
    void on_planTrip_stadiums_tableWidget_doubleClicked(const QModelIndex &index);

    void on_planTrip_stadiumsChosen_tableWidget_doubleClicked(const QModelIndex &index);

    void on_planTrip_toolButton_moveUp_clicked();

    void on_planTrip_toolButton_moveDown_clicked();

private:
    Ui::PlanTrip *ui;
};

#endif // PLANTRIP_H
