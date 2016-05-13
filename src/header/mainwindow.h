#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QString>
#include <QStack>
#include <QMessageBox>
#include "../header/adminlogin.h"
#include "../header/stadiumdetails.h"
#include "../header/homepage.h"
#include "../header/editstadiuminfo.h"
#include "../header/plantrip.h"
#include "../header/purchasewindow.h"
#include "../header/tripsummary.h"
#include "../header/database.h"
#include "../header/stadiumtablemodel.h"
#include "../header/souvenirtablemodel.h"
#include <QDebug>

namespace Ui {
class MainWindow;
}

enum pages
{
    PAGE_MAIN,
    PAGE_SPLASH,
    PAGE_HOME,
    PAGE_PLAN_TRIP,
    PAGE_STADIUM_DETAILS,
    PAGE_PURCHASE_WINDOW,
    PAGE_EDIT_STADIUM_INFO,
    PAGE_TRIP_SUMMARY
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void initializeStadiumTable(StadiumTableModel *stadiumModel);
    void initializeSouvenirTable(SouvenirTableModel *souvenirModel);
    void adminFeaturesToggled(bool);
    void giveDB(Database *db);
    void propagateStadiumList(QSqlQuery);

private slots:
    void clickNext();

    void toggleAdminFeatures(bool isAdmin);

    void on_mainwindow_pushButton_next_clicked();

    void on_mainwindow_pushButton_planTrip_clicked();

    void on_mainwindow_pushButton_back_clicked();

    void on_mainwindow_pushButton_viewStadiums_clicked();

    void gotoHomePage();

    void on_actionLogin_triggered();

    void on_actionLogout_triggered();

    void hideNextButton(bool hidden);

private:
    Ui::MainWindow *  ui;
    StadiumDetails*   stadiumDetails_widget;
    HomePage*         homePage_widget;
    PlanTrip*         planTrip_widget;
    PurchaseWindow*   purchaseWindow_widget;
    EditStadiumInfo*  editStadiumInfo_widget;
    TripSummary*      tripSummary_widget;
    QStack<int>       pageStackCache;
    Database*         db;
    StadiumTableModel* stadiumModel;
    SouvenirTableModel* souvenirModel;

    void checkPage_toggleBackNextButtonVisible();
    void leavingTripSummary();

};

#endif // MAINWINDOW_H
