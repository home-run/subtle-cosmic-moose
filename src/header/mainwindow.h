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
    QMap<QString, int>	widgetMap;		// Will store the index of all the widgets-windows we use
    StadiumDetails* stadiumDetails_widget;
    HomePage*	homePage_widget;

    // Private methods to MainWindow
private:
    int getWidgetIndexFromMap(QString widgetName);

};

#endif // MAINWINDOW_H
