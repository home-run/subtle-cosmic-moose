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

    /**
     * @brief populateTripPath
     * @param pathOfTrip
     * Takes in a QList of <Vertex> to be displayed on the list, assumes the
     * list is ordered in the sortest path
     */
    void populateTripPath(QList<Vertex> pathOfTrip);

    /**
     * @brief clearData
     * Clears the data on the list so that it can be reused for next time
     */
    void clearData();

private slots:
    void on_tripSummary_pushButton_finishTripSummary_clicked();

    /**
     * @brief TripSummary::accept_plannedTrip_listOfStadiums(QStringList);
     * Will be called to accept a list of stadiums to visit so we can populate
     * the final table, how the list will be ordered and printed will be
     * determined by the algorithm.
     * */
    void accept_plannedTrip_listOfStadiums(QStringList);

private:
    Ui::TripSummary *ui;
    Database *db;
};

#endif // TRIPSUMMARY_H
