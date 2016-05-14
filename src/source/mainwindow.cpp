#include "../header/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("~/run Dream Vacation Planner");
    this->setWindowIcon(QIcon(":/icons/resources_icons/program_icon.png"));

    // Instantiate database
    db = new Database("data.db", "QSQLITE");

    // Allocate memory for all the different widget pages
    stadiumDetails_widget 	= new StadiumDetails(this, db);
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
    connect(this, SIGNAL(initializeStadiumTable(StadiumTableModel*)),
            stadiumDetails_widget, SLOT(initializeStadiumTable(StadiumTableModel*)));
    connect(this, SIGNAL(initializeSouvenirTable(SouvenirTableModel*)),
            stadiumDetails_widget, SLOT(initializeSouvenirTable(SouvenirTableModel*)));
    connect(this, SIGNAL(adminFeaturesToggled(bool)),
            stadiumDetails_widget, SLOT(toggleAdminFunctions(bool)));
    //Splash Screen Emits signal when done, call gotoHomePage Function
    connect(homePage_widget, SIGNAL(isFinished(bool)), this, SLOT(gotoHomePage()));

    //Start off with splash screen
    ui->mainwindow_stackedWidget->setCurrentIndex(PAGE_HOME);

    // toggle hiding of back/next button
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
 * @brief MainWindow::toggleAdminFeatures
 * Emit a signal that activates or deactivates all admin features.
 * @param isAdmin true if user is an admin
 */
void MainWindow::toggleAdminFeatures(bool isAdmin)
{
    emit adminFeaturesToggled(isAdmin);
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
        //Disables the Spacer
        ui->mainwindow_horizontalSpacer_buttons->changeSize(0, 60, QSizePolicy::Fixed);
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
        //Enable Spacer
        ui->mainwindow_horizontalSpacer_buttons->changeSize(40,60,QSizePolicy::Minimum);
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
    //Disables the Spacer
    ui->mainwindow_horizontalSpacer_buttons->changeSize(0, 60, QSizePolicy::Fixed);

    // initialize tables with data from database
    stadiumModel = new StadiumTableModel(this, db);
    souvenirModel = new SouvenirTableModel(this, db);
    emit initializeStadiumTable(stadiumModel);
    emit initializeSouvenirTable(souvenirModel);
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
    // TODO: CLEAR DATA IN ALL CURRENT WIDGETS
    ui->mainwindow_stackedWidget->setCurrentIndex(PAGE_MAIN);
    checkPage_hideShowBackNextButton();
    pageStackCache.clear();
}


/*
 QFile file(":/qss/darkorange.qss");
 if(file.open(QIODevice::ReadOnly | QIODevice::Text))
 {
     setStyleSheet(file.readAll());
     file.close();
 }
 */

/**
 * @brief MainWindow::on_actionLogin_triggered
 * Prompt the user for an admin password. If it's legit, send a signalx that
 * grants access to all admin functions in the application.
 */
void MainWindow::on_actionLogin_triggered()
{
    AdminLogin *adminPrompt = new AdminLogin(this);
    QObject::connect(adminPrompt, SIGNAL(adminStatusChanged(bool)),
                     this, SLOT(toggleAdminFeatures(bool)));
    adminPrompt->setWindowModality(Qt::ApplicationModal);
    adminPrompt->show();
}

/**
 * @brief MainWindow::on_actionLogout_triggered
 * Log the admin out and disable all of the admin features.
 */
void MainWindow::on_actionLogout_triggered()
{
    emit adminFeaturesToggled(false);
}

/*!
 * \brief MainWindow::on_actionAdd_new_stadium_triggered
 * @brief Adds stdaium with its corresponding attritbutes
 * @brief Adds edges with weights between Lags Vegas and it surrounding cities.
 * @brief Adds souviers to Lag Vegas stdium
 *
 */
void MainWindow::on_actionAdd_new_stadium_triggered()
{
    db->AddStadium("Las Vegas Stadium","Las Vegas Gamblers","123 Las Vegas Blv,NV 89101","(702) 962-4000","2016-04-11","50,000","Grass",0,"American","Modern");
    int id =  db->GetStadiumID("Las Vegas Stadium");
    qDebug()<<"ID; "<<id;
    db->AddDistance(id,7,325);
    db->AddDistance(id,22,300);
    db->AddDistance(id,18,250);


    db->AddSouvenir("Las Vegas Stadium","Baseball cap",23.99);
    db->AddSouvenir("Las Vegas Stadium","Baseball bat",45.39);
    db->AddSouvenir("Las Vegas Stadium","Team pendant",15.39);
    db->AddSouvenir("Las Vegas Stadium","Autographed baseball",19.99);

    // initialize tables with data from database
    stadiumModel = new StadiumTableModel(this, db);
    souvenirModel = new SouvenirTableModel(this, db);
    emit initializeStadiumTable(stadiumModel);
    emit initializeSouvenirTable(souvenirModel);
}

