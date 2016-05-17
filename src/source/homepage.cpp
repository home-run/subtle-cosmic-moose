#include "header/homepage.h"
#include "ui_homepage.h"
#include "QMovie"
#include "QDebug"
#include "QString"
#include "QMediaPlayer"

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);

    //Initialize the splash screen and allow user to exit if they click on it
    QMovie *splashImg = new QMovie(":/icons/resources_icons/ProjectLogo_LoopOnce.gif");
    ui->label->setMovie(splashImg);
    ui->label->setFixedSize(900,450);

    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/audio/resources_icons/ProjectLogoSound.mp3"));
    player->setVolume(100);
    player->setPlaybackRate(0.85);
    player->play();


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

