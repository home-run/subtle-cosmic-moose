#ifndef STADIUMDETAILS_H
#define STADIUMDETAILS_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include "addsouvenir.h"
#include "stadiumtablemodel.h"
#include "souvenirtablemodel.h"

namespace Ui {
class StadiumDetails;
}

class StadiumDetails : public QWidget
{
    Q_OBJECT

public:
    explicit StadiumDetails(QWidget *parent = 0, Database *db = 0);

    void initializeStadiumView();

    void initializeSouvenirView();

    ~StadiumDetails();

public slots:
    void refreshModels();
    void toggleAdminFunctions(bool isAdmin);
    void initializeStadiumTable(StadiumTableModel *stadiumModel);
    void initializeSouvenirTable(SouvenirTableModel *souvenirModel);

private slots:
    void on_stadiumDetails_league_comboBox_currentIndexChanged(int index);

    void on_stadiumDetails_surface_comboBox_currentIndexChanged(int index);

    void on_stadiumDetails_tableView_stadiumInfo_clicked(const QModelIndex &index);

    void on_stadiumDetails_tableView_stadiumInfo_activated(const QModelIndex &index);

    void on_stadiumDetails_admin_submitChanges_clicked();

    void on_stadiumDetails_admin_addSouvenir_clicked();

    void on_stadiumDetails_admin_removeSouvenir_clicked();

private:
    Ui::StadiumDetails *ui;
    StadiumTableModel *stadiumModel;
    SouvenirTableModel *souvenirModel;
    Database *db;
};

#endif // STADIUMDETAILS_H
