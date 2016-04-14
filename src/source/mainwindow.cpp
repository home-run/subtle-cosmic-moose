#include "../header/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Allocate memory for all the different widget pages
    stadiumDetails_widget 	= new StadiumDetails();
    homePage_widget 		= new HomePage();
    planTrip_widget 		= new PlanTrip();
    editStadiumInfo_widget 	= new EditStadiumInfo();
    purchaseWindow_widget 	= new PurchaseWindow();

    // Add widgets to the stacked widget
    ui->mainwindow_stackedWidget->addWidget(stadiumDetails_widget);
    ui->mainwindow_stackedWidget->addWidget(homePage_widget);
    ui->mainwindow_stackedWidget->addWidget(planTrip_widget);
    ui->mainwindow_stackedWidget->addWidget(editStadiumInfo_widget);
    ui->mainwindow_stackedWidget->addWidget(purchaseWindow_widget);
}

MainWindow::~MainWindow()
{
    // This will need to be refactored to handle the saving of information if they
    //	are not excplicitly controlling any data.
    delete stadiumDetails_widget;
    delete homePage_widget;
    delete editStadiumInfo_widget;
    delete purchaseWindow_widget;
    delete planTrip_widget;
    delete ui;
}

/**
 * @brief MainWindow::on_mainwindow_pushButton_next_clicked
 * This is an example of how to cycle through all the widgets in the main window
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
        currentIndex = 1;
    }
    ui->mainwindow_stackedWidget->setCurrentIndex(currentIndex);
}
