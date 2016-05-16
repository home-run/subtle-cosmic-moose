#ifndef TRIPSUMMARY_H
#define TRIPSUMMARY_H

#include <QWidget>
#include <graph.h>
#include <purchasewindow.h>

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
     * Takes in a QList of <Vertex> to be displayed on the list, assumes the
     * list is ordered in the sortest path
     * @param pathOfTrip
     */
    void populateTripPath(QList<Vertex> pathOfTrip);

    /**
     * @brief populatePurchaseReciept
     * This method will take in the purchase table and display the users total spent
     * When the item is hovered over, it will tell you the total revenue of the stadium
     * that sovenir came from
     * @param purchases - QList of Structure purchaseInfo
     */
    void populatePurchaseReciept(QList<PurchaseWindow::purchaseInfo> purchases);

    /**
     * @brief clearData
     * Clears the data on the list so that it can be reused for next time
     */
    void clearData();

private slots:
    /**
     * @brief on_tripSummary_pushButton_finishTripSummary_clicked
     * Press the finish button and clear all data and return to Main Page
     */
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
