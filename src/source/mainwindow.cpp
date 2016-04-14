#include "../header/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    stadiumDetails_widget = new StadiumDetails();
    homePage_widget = new HomePage();

    ui->setupUi(this);

    ui->mainwindow_stackedWidget->addWidget(stadiumDetails_widget);
    ui->mainwindow_stackedWidget->addWidget(homePage_widget);
}

MainWindow::~MainWindow()
{
    delete stadiumDetails_widget;
    delete homePage_widget;
    delete ui;
}

/**
 * @brief MainWindow::on_mainwindow_pushButton_next_clicked
 * This is an example of how to changed the widgets on a stacked widget using a QMap
 * implementation for finding an index
 */
void MainWindow::on_mainwindow_pushButton_next_clicked()
{
//    int widgetIndex;
    int currentIndex;

    currentIndex = ui->mainwindow_stackedWidget->currentIndex();
    qDebug() << "Current index is : " << currentIndex;

    currentIndex++;

    qDebug() << "New index is : " << currentIndex;
    if(currentIndex >= ui->mainwindow_stackedWidget->count())
    {
        currentIndex = 0;
    }
    ui->mainwindow_stackedWidget->setCurrentIndex(currentIndex);
}
