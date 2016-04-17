#include "../header/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Instantiate database
    db = new Database("data.db", "QSQLITE");

    // Allocate memory for all the different widget pages
    stadiumDetails_widget 	= new StadiumDetails();
    homePage_widget 		= new HomePage();
    planTrip_widget 		= new PlanTrip();
    editStadiumInfo_widget 	= new EditStadiumInfo();
    purchaseWindow_widget 	= new PurchaseWindow();
    tripSummary_widget      = new TripSummary();

    // Add widgets to the stacked widget
    ui->mainwindow_stackedWidget->addWidget(homePage_widget);
    ui->mainwindow_stackedWidget->addWidget(planTrip_widget);
    ui->mainwindow_stackedWidget->addWidget(stadiumDetails_widget);
    ui->mainwindow_stackedWidget->addWidget(purchaseWindow_widget);
    ui->mainwindow_stackedWidget->addWidget(editStadiumInfo_widget);
    ui->mainwindow_stackedWidget->addWidget(tripSummary_widget);

    //Connections to Widgets
    connect(tripSummary_widget, SIGNAL(finishTrip(bool)), this, SLOT(gotoHomePage()));

    checkPage_hideShowBackNextButton();
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
    delete tripSummary_widget;
    delete ui;
}


/**
 * @brief MainWindow::on_mainwindow_pushButton_next_clicked
 * This is an example of how to cycle through all the widgets in the main window
 */
void MainWindow::on_mainwindow_pushButton_next_clicked()
{
    int currentIndex;

    // set currentIndex to current stackedWidget index
    currentIndex = ui->mainwindow_stackedWidget->currentIndex();

    // push this index to the stack (for back button)
    pageStackCache.push(currentIndex);

    // do different things based on which page gets called
    switch(currentIndex)
    {
    case PAGE_PLAN_TRIP:
        ui->mainwindow_stackedWidget->setCurrentIndex(PAGE_PURCHASE_WINDOW);
        break;
    case PAGE_PURCHASE_WINDOW:
        ui->mainwindow_stackedWidget->setCurrentIndex(PAGE_TRIP_SUMMARY);
        tripSummary_widget->populateTripPath();
        ui->mainwindow_pushButton_next->setVisible(false);
        break;
    default:
        ui->mainwindow_stackedWidget->setCurrentIndex(currentIndex);
        checkPage_hideShowBackNextButton();
        break;
    }
}

/**
 * @brief MainWindow::on_mainwindow_pushButton_planTrip_clicked
 * This method will take the user from main page to the plan a trip page. It also
 * will push the current stacked widget index to a index stack cache.
 */
void MainWindow::on_mainwindow_pushButton_planTrip_clicked()
{
    int currentIndex;
    currentIndex = ui->mainwindow_stackedWidget->currentIndex();
    pageStackCache.push(currentIndex);
    this->planTrip_widget->propagateStadiumTable(db);
    ui->mainwindow_stackedWidget->setCurrentIndex(PAGE_PLAN_TRIP);
    checkPage_hideShowBackNextButton();
}

/**
 * @brief MainWindow::on_mainwindow_pushButton_back_clicked
 *   This method will get the previous index in a cached stack of widget indices.
 * It will check if the stack is empty then pop off the stack cache and set it as the
 * index as the current stacked widget.
 */
void MainWindow::on_mainwindow_pushButton_back_clicked()
{
    // Should probably implement a feature to save any current data that is being modified.
    int currentIndex;

    // Check if the stack is empty
    if(!pageStackCache.isEmpty())
    {
        switch(ui->mainwindow_stackedWidget->currentIndex())
        {
        case PAGE_TRIP_SUMMARY : tripSummary_widget->clearData();
            break;
        }

        // Remove the current index
        currentIndex = pageStackCache.pop();
        // Set the stacked widget to the previous index
        ui->mainwindow_stackedWidget->setCurrentIndex(currentIndex);
    }
    checkPage_hideShowBackNextButton();


}

/**
 * @brief MainWindow::checkPage_hideShowBackNextButton
 * Toggle the visibility of the back and next button based on which page
 * is being viewed.
 */
void MainWindow::checkPage_hideShowBackNextButton()
{
    if(pageStackCache.isEmpty() || ui->mainwindow_stackedWidget->currentIndex() < 2)
    {
        ui->mainwindow_pushButton_back->setVisible(false);
        ui->mainwindow_pushButton_next->setVisible(false);
    }
    else
    {
        ui->mainwindow_pushButton_back->setVisible(true);
        ui->mainwindow_pushButton_next->setVisible(true);
    }
}

/**
 * @brief MainWindow::on_mainwindow_pushButton_viewStadiums_clicked
 */
void MainWindow::on_mainwindow_pushButton_viewStadiums_clicked()
{
    // set current index to the current stackedWidget index
    int currentIndex;
    currentIndex = ui->mainwindow_stackedWidget->currentIndex();

    // push index to the stack for back button
    pageStackCache.push(currentIndex);

    // set current page to stadium details page
    ui->mainwindow_stackedWidget->setCurrentIndex(PAGE_STADIUM_DETAILS);

    // toggle visibility of back/next button
    checkPage_hideShowBackNextButton();
    ui->mainwindow_pushButton_next->setVisible(false);

    // initialize tables with data from database
}

void MainWindow::leavingTripSummary()
{
    tripSummary_widget->clearData();
}

/**
 * @brief MainWindow::gotoHomePage
 * Function to bring the application back to the home page, clear the stack cache and
 * any other data widgets.
 */
void MainWindow::gotoHomePage()
{
    /// TODO: CLEAR DATA IN ALL CURRENT WIDGETS
    ui->mainwindow_stackedWidget->setCurrentIndex(PAGE_MAIN);
    checkPage_hideShowBackNextButton();
    pageStackCache.clear();
}

