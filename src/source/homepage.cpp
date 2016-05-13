#include "header/homepage.h"
#include "ui_homepage.h"
#include "QMovie"
#include "QDebug"
#include "QString"

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);

    //Initialize the splash screen and allow user to exit if they click on it
    QMovie *splashImg = new QMovie(":/icons/resources_icons/ProjectLogo_LoopOnce.gif");
    ui->label->setMovie(splashImg);
    ui->label->setFixedSize(900,450);

    //Connect the signal on every frame change to check for last frame since it loops infinitely
    connect(splashImg, SIGNAL(finished()), this, SLOT(EmitFinished()));
    splashImg->start();

}

HomePage::~HomePage()
{
    delete ui;
}

/**
 * @brief HomePage::EmitFinished()
 * Checks the for the last frame of the Qmovie and emits a signal when done
 */
void HomePage::EmitFinished()
{
    qDebug("Emitted Finished signal for SPLASHSCREEN");
    emit isFinished(true);
}

