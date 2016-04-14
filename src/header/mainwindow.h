#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QString>
#include "../header/stadiumdetails.h"
#include "../header/homepage.h"
#include <QDebug>

namespace Ui {
class MainWindow;
}

enum pages
{
    PAGE_SPLASH,
    PAGE_HOME,
    PAGE_STADIUM_DETAILS,
    PAGE_PLAN_TRIP,
    PAGE_PURCHASE_WINDOW,
    PAGE_EDIT_STADIUM_INFO
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_mainwindow_pushButton_next_clicked();

private:
    Ui::MainWindow *ui;
    StadiumDetails* stadiumDetails_widget;
    HomePage*	homePage_widget;

};

#endif // MAINWINDOW_H
