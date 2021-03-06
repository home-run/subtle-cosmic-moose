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
void TripSummary::populateTripPath(QList<Vertex> postAlgorithmList, bool isCustomTrip)
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
                if(isCustomTrip)
                {
                //Nicely formatted string~ the beauty of laziness
                itemToAppend = QString("From %1 -> %2 : Distance [%3]")
                        .arg(sourceStadium, destinationStadium, distanceBetween);

                //Go ahead and add to the list widget
                ui->tripSummary_listWidget_tripPath->addItem(itemToAppend);

                }
                else//Not custom trip but Visit All from Dogers
                {
                    //If we hit another Dogers Stadium not at first index,
                    //stop trip distance accumulation, start new.
                    if(sourceStadium == "Dodger Stadium" && index != 1)
                    {
                        //Print out Total distances till now
                        ui->tripSummary_listWidget_tripPath->addItem(
                                    QString("---TOTAL DISTANCE TRAVELED: [%1]---")
                                    .arg(totalDistancesTraveled));
                        totalDistancesTraveled = 0;

                        //Nicely formatted string~ the beauty of laziness
                        itemToAppend = QString("<START> From %1 -> %2 : Distance [%3]")
                                .arg(sourceStadium, destinationStadium, distanceBetween);
                    }
                    else //continue on with the regular printing
                    {
                        //Nicely formatted string~ the beauty of laziness
                        itemToAppend = QString("From %1 -> %2 : Distance [%3]")
                                .arg(sourceStadium, destinationStadium, distanceBetween);

                    }

                    //Go ahead and add to the list widget
                    ui->tripSummary_listWidget_tripPath->addItem(itemToAppend);
                }

                //Add the distance total
                totalDistancesTraveled += distanceBetween.toInt();
            }
        }
        //Else don't append it

    }

    //Go ahead and add to the list widget
    ui->tripSummary_listWidget_tripPath->addItem(
                QString("TOTAL DISTANCE TRAVELED: [%1 Miles]")
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

    //Declare some variables
    QString name, price, quantity, stadium;
    QString purchaseStructToAppend;
    double totalPriceOfPurchase;

    //Loop to get all items
    for(int index = 0; index < purchases.size(); index++)
    {
        //copy all data over
        stadium = purchases.at(index).stadiumName;
        name = purchases.at(index).itemName;
        price = QString::number(purchases.at(index).itemPrice);
        quantity = QString::number(purchases.at(index).quantity);

        //Preformat dat shizzle
        stadium = stadium.leftJustified(30, ' ');
        name = name.leftJustified(30-name.size(), ' ');
        price = price.leftJustified(6-price.size(), ' ');
        quantity = quantity.leftJustified(3-quantity.size(), ' ');

        //Put into a giant string
        purchaseStructToAppend =
                QString("Purchased From: %1\tItem Name: %2\tItem Price: %3\tQuantity: %4")
                .arg(stadium,name,price,quantity);

        //Continually accumulate the total purchase price
        totalPriceOfPurchase += (purchases.at(index).itemPrice * purchases.at(index).quantity);

        //Add all data to the list itself
        ui->tripSummary_listWidget_Purchases->addItem(purchaseStructToAppend);

        // Add revenues to stadiums
        db->AddRevenue(db->GetStadiumID(purchases.at(index).stadiumName), (purchases.at(index).itemPrice * purchases.at(index).quantity));

    }

    //Final total purchase of the trip
    QString totalPurchased;

    //If we had purchases
    if(totalPriceOfPurchase != 0)
    {
    totalPurchased = QString("Your Total Amount is: $%1")
                            .arg(QString::number(totalPriceOfPurchase));
    }
    else //We had no purchases
    {
        totalPurchased = "You had no purchases!";
    }

    //Add the total purchase
    ui->tripSummary_listWidget_Purchases->addItem(totalPurchased);

}

/**
 * @brief TripSummary::clearData
 * Clears the two lists
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

    //Get A list of ID numbers related to the stops in dream vacation
    QList<int> stops;
    for (int index = 0; index < stadiumList.size(); ++index)
    {
        //Offset ID numbers by 1 to get actual positions in the vertexList inside Graph
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

/**
 * @brief TripSummary::accept_visitAllStadiums
 * Accepts the signal to run the Visit all Stadiums algorithm in order
 * to populate the table with data
 */
void TripSummary::accept_visitAllStadiums()
{
    //Clear table just in case
    clearData();

    Graph graph;
    graph.createGraph(db);

    populateTripPath(graph.getDodgerStadiumPath(), false);
}
