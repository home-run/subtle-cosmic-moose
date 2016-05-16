#include "header/tripsummary.h"
#include "ui_tripsummary.h"

TripSummary::TripSummary(QWidget *parent, Database *db) :
    QWidget(parent),
    ui(new Ui::TripSummary)
{
    ui->setupUi(this);

    // Set local db pointer to the database.
    this->db = db;

}

TripSummary::~TripSummary()
{
    delete ui;
}

/**
 * @brief TripSummary::populateTripPath
 * Method will populate the trip path list with given data from the algorithm.
 */
void TripSummary::populateTripPath(QList<Vertex> postAlgorithmList)
{
    //Item to Append to the list to be displayed as per row
    QString itemToAppend;
    Graph graph;
    graph.createGraph(db);
    int totalDistancesTraveled = 0;

    for(int index = 0; index < postAlgorithmList.size(); index++)
    {
        QString sourceStadium, destinationStadium, distanceBetween;

        //Case 0th index, starting off at source
        if(index == 0)
        {

            sourceStadium = "STARTING STADIUM";
            destinationStadium = postAlgorithmList.at(index).getName();
            distanceBetween = QString::number(0);

            //Nicely formatted string~ the beauty of laziness
            itemToAppend = QString("%1 -> %2 : Distance [%3]")
                    .arg(sourceStadium, destinationStadium, distanceBetween);

            //Go ahead and add to the list widget
            ui->tripSummary_listWidget_tripPath->addItem(itemToAppend);

        }
        else //Otherwise
        {
            //Grab all data related to the path
            //Offset by 1 to get source
            sourceStadium = postAlgorithmList.at(index-1).getName();
            //Destination is current index
            destinationStadium = postAlgorithmList.at(index).getName();
            //Edge of the distance traveled
            distanceBetween = QString::number
                    (
                        graph.edgeWeight
                        (
                            db->GetStadiumID(sourceStadium)-1,
                            db->GetStadiumID(destinationStadium)-1
                        )
                    );

            //Check for 0 distance paths, we are not traveling anywhere
            if(distanceBetween.toInt() != 0)
            {
                //Nicely formatted string~ the beauty of laziness
                itemToAppend = QString("From %1 -> %2 : Distance [%3]")
                        .arg(sourceStadium, destinationStadium, distanceBetween);

                //Go ahead and add to the list widget
                ui->tripSummary_listWidget_tripPath->addItem(itemToAppend);

                //Total Distance accumulator
                totalDistancesTraveled += distanceBetween.toInt();
            }
        }
        //Else don't append it

    }

    //Go ahead and add to the list widget
    ui->tripSummary_listWidget_tripPath->addItem(
                QString("TOTAL DISTANCE TRAVELED: [%1]")
                .arg(totalDistancesTraveled));
}

/**
 * @brief TripSummary::populatePurchaseReciept
 * Populates the List widget with the information of purchases
 * @param purchases
 */
void TripSummary::populatePurchaseReciept(QList<PurchaseWindow::purchaseInfo> purchases)
{
    //Initial line for purchase reciept
    ui->tripSummary_listWidget_Purchases->addItem(QString("****PURCHASE RECIEPT****"));

    double totalPriceOfPurchase;

    //Loop to get all items
    for(int index = 0; index < purchases.size(); index++)
    {
        //copy all data over
        QString name, price, quantity, stadium;
        stadium = purchases.at(index).stadiumName;
        name = purchases.at(index).itemName;
        price.number(purchases.at(index).itemPrice);
        quantity.number(purchases.at(index).quantity);

        //Put into a giant string
        QString purchaseStructToAppend = QString("Purchased From: %1\tItem Name: %2\tItem Price: %3\tQuantity: %4")
                .arg(stadium,name,price,quantity);

        totalPriceOfPurchase += purchases.at(index).itemPrice;

        //TODO - Display statium totals in a tooltip
        QListWidgetItem *purchaseItem = new QListWidgetItem(purchaseStructToAppend);
        purchaseItem->setToolTip(QString("<Insert Item's Stadium Total Rev here>"));

        //Add all data to the list itself
        ui->tripSummary_listWidget_Purchases->addItem(purchaseItem);

    }

    //Final total purchase of the trip
    QString totalPurchased("Your Total Amount is: ");
    totalPurchased.append(QString::number(totalPriceOfPurchase));

    //Add the total purchase
    ui->tripSummary_listWidget_Purchases->addItem(totalPurchased);
}

/**
 * @brief TripSummary::clearData
 * Clears the list
 */
void TripSummary::clearData()
{
    ui->tripSummary_listWidget_tripPath->clear();
    ui->tripSummary_listWidget_Purchases->clear();
}

/**
 * @brief TripSummary::on_tripSummary_pushButton_finishTripSummary_clicked
 * Signal for the finish button, clears data and finish the Trip
 */
void TripSummary::on_tripSummary_pushButton_finishTripSummary_clicked()
{
    emit(finishTrip(true));
    clearData();
}

/**
 * @brief TripSummary::accept_plannedTrip_listOfStadiums
 * @param stadiumList - QStringList of Stadiums
 * Runs after it catches the signal
 */
void TripSummary::accept_plannedTrip_listOfStadiums(QStringList stadiumList)
{
    //Clear data before it runs in again
    clearData();

    //Initialize the graph
    Graph graphOfStadiums;
    graphOfStadiums.createGraph(db);

//    //assign id numbers
//    int sourceID, destinationID;
//    //Offset ID numbers by 1 to get actual positions in the vertexList inside Graph
//    sourceID = db->GetStadiumID(stadiumList.at(0)) - 1;
//    destinationID = db->GetStadiumID(stadiumList.at(stadiumList.size()-1)) - 1;

//    //Call populateTripPath() to write to list
//    populateTripPath(graphOfStadiums.findShortestPathTo(db, sourceID, destinationID));


    QList<int> stops;
    for (int index = 0; index < stadiumList.size(); ++index)
    {
        int id = db->GetStadiumID(stadiumList.at(index)) -1;
        qDebug() << id;
        stops.append(id);
    }

    qDebug() << "*****Inside Returned QList<Vertex>*******";

    //Get a List of vertex to be passed into the populate Trip Path
    QList<Vertex> vertexList;
    vertexList = graphOfStadiums.findShortestPathTo(db, stops.at(0), stops);

    populateTripPath(vertexList);
}
