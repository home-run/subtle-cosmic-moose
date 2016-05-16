#ifndef PLANTRIP_H
#define PLANTRIP_H

#include <QtSql/QtSql>
#include <QMessageBox>
#include <QWidget>
#include "database.h"

namespace Ui {
class PlanTrip;
}

class PlanTrip : public QWidget
{
    Q_OBJECT

public:
    explicit PlanTrip(QWidget *parent = 0, Database *db = 0);

    ~PlanTrip();

signals:
    /// Send a signal to hide or show the mainwindow next button.
    void hideNextButton(bool);

    /// Send a signal to click the mainwindow next button.
    void clickNext();

    /// Send a signal with a stringList containing the selected stadiums, in order.
    void giveStadiumList(QStringList);

    /// Sends a signal saying we clicked the visit all button
    void callVisitAll();

    /// Sends a signal for Visitall Stadiums for purchase cart
    void giveStadiumListVisitAll(QStringList);

    /// Send a signal to display the minimum spanning tree.
    void displayMST();

public slots:
    /// Propagate the stadiums list.
    void propagateStadiumList(QSqlQuery query);

private slots:
    /// Add a stadium to the selected stadiums list on double-click.
    void on_planTrip_stadiums_tableWidget_doubleClicked(const QModelIndex &index);

    /// Remove a stadium from the selected stadiums list on double-click.
    void on_planTrip_stadiumsChosen_tableWidget_doubleClicked(const QModelIndex &index);

    /// Move an item up in the selected stadiums list.
    void on_planTrip_toolButton_moveUp_clicked();

    /// Move an item down in the selected stadiums list.
    void on_planTrip_toolButton_moveDown_clicked();

    /// Plan a dream vacation
    void on_planTrip_pushButton_dreamVacation_clicked();

    /// Add a stadium to the selected stadiums list.
    void on_planTrip_toolButton_add_clicked();

    /// Remove a stadium from the selected stadiums list.
    void on_planTrip_toolButton_remove_clicked();

    /// When the Visit All Stadiums button is clicked
    void on_planTrip_pushButton_visitAll_clicked();

    /// When the MST button is clicked
    void on_planTrip_pushButton_MST_clicked();

private:
    Ui::PlanTrip *ui;
    Database *db;
};

#endif // PLANTRIP_H
