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
    QMovie *splashImg = new QMovie(":/icons/resources_icons/pitcher_animated_full.gif");
    ui->label->setMovie(splashImg);
    ui->label->setFixedSize(450,450);

    //Connect the signal on every frame change to check for last frame since it loops infinitely
    connect(splashImg, SIGNAL(frameChanged(int)), this, SLOT(CheckLastFrame(int)));
    splashImg->start();

    //Debug statement
    qDebug() << "Frame Count: " << splashImg->frameCount();

}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::CheckLastFrame(int frame)
{
    if(frame >= 150)
    {
        this->close();
    }
}
