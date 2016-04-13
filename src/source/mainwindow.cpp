#include "../header/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    stadiumDetails_widget = new StadiumDetails();

    ui->setupUi(this);
    // Here we set a string as the key to the index value at which stadium Details is added
    //	to the widget map. This will allow us search for the index of the widget to be
    //	used when changing which widget the stackedWidget is displaying.
    widgetMap.insert("Stadium Details",  ui->mainwindow_stackedWidget->addWidget(stadiumDetails_widget) );


}

MainWindow::~MainWindow()
{
    delete stadiumDetails_widget;
    delete ui;
}

/**
 * @brief MainWindow::on_mainwindow_pushButton_next_clicked
 * This is an example of how to changed the widgets on a stacked widget using a QMap
 * implementation for finding an index
 */
void MainWindow::on_mainwindow_pushButton_next_clicked()
{
    int widgetIndex;
    widgetIndex = getWidgetIndexFromMap("Stadium Details");
    if(widgetIndex != -1)
    {
        ui->mainwindow_stackedWidget->setCurrentIndex(widgetIndex);
    }
}

/**
 * @brief MainWindow::getWidgetIndexFromMap
 * This function will take the name of the widget that you are looking for in the stacked
 * widget and return the index of that widget in the QMap. This index should be used
 * by the stacked widget to set its current index.
 * @param widgetName
 * @return integer index of the widget name
 */
int MainWindow::getWidgetIndexFromMap(QString widgetName)
{
    QMap<QString, int>::iterator widgetIterator;
    int widgetIndex;
    widgetIterator = widgetMap.find(widgetName);
    if(widgetIterator == widgetMap.end())
    {
        widgetIndex = -1;
    }
    else
    {
        widgetIndex = widgetIterator.value();
    }

    return widgetIndex;
}
