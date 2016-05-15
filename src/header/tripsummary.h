#ifndef TRIPSUMMARY_H
#define TRIPSUMMARY_H

#include <QWidget>
#include <graph.h>

namespace Ui {
class TripSummary;
}

class TripSummary : public QWidget
{
    Q_OBJECT

signals:
    /// Send a signal when the user presses the finish button
    void finishTrip(bool);

public:
    explicit TripSummary(QWidget *parent = 0,  Database *db = 0);
    ~TripSummary();

    //Function populates listWidget with a string
    void clearData();

private slots:
    void on_tripSummary_pushButton_finishTripSummary_clicked();

private:
    Ui::TripSummary *ui;
};

#endif // TRIPSUMMARY_H
