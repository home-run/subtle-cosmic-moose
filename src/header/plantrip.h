#ifndef PLANTRIP_H
#define PLANTRIP_H

#include <QWidget>

namespace Ui {
class PlanTrip;
}

class PlanTrip : public QWidget
{
    Q_OBJECT

public:
    explicit PlanTrip(QWidget *parent = 0);
    ~PlanTrip();

private:
    Ui::PlanTrip *ui;
};

#endif // PLANTRIP_H
