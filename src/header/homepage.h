#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>

namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = 0);
    ~HomePage();

private slots:
    //FIXME Debug limitter for gif
    //Checks the for the last frame of the Qmovie and close window if it is
    void CheckLastFrame(int frame);

private:
    Ui::HomePage *ui;
};

#endif // HOMEPAGE_H
