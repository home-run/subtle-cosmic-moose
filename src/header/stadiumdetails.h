#ifndef STADIUMDETAILS_H
#define STADIUMDETAILS_H

#include <QWidget>
#include "stadiumtablemodel.h"

namespace Ui {
class StadiumDetails;
}

class StadiumDetails : public QWidget
{
    Q_OBJECT

public:
    explicit StadiumDetails(QWidget *parent = 0);
    void initializeStadiumView();
    ~StadiumDetails();

public slots:
    void initializeStadiumTable(StadiumTableModel *stadiumModel);

private:
    Ui::StadiumDetails *ui;
    StadiumTableModel *stadiumModel;
};

#endif // STADIUMDETAILS_H
