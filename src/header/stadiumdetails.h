#ifndef STADIUMDETAILS_H
#define STADIUMDETAILS_H

#include <QWidget>

namespace Ui {
class StadiumDetails;
}

class StadiumDetails : public QWidget
{
    Q_OBJECT

public:
    explicit StadiumDetails(QWidget *parent = 0);
    ~StadiumDetails();

private:
    Ui::StadiumDetails *ui;
};

#endif // STADIUMDETAILS_H
