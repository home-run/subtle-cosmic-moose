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


    for(int index = 0; index < postAlgorithmList.size(); index++)
    {
        QString sourceStadium, destinationStadium, distanceBetween;

        switch(index)
        {
        //Case 0th index, starting off at source
        case 0:
            sourceStadium = "STARTING STADIUM";
            destinationStadium = postAlgorithmList.at(index).getName();
            distanceBetween = QString::number(0);


            //Nicely formatted string~ the beauty of laziness
            itemToAppend = QString("%1 -> %2 : Distance [%3]")
                    .arg(sourceStadium, destinationStadium, distanceBetween);
            break;

        default:
            //Offset by 1 to get source
            sourceStadium = postAlgorithmList.at(index-1).getName();
            //Destination is current index
            destinationStadium = postAlgorithmList.at(index).getName();
            //Sum of total distances - sum of total distances of previous node
            distanceBetween =
            QString::number(postAlgorithmList.at(index).getDistance() - postAlgorithmList.at(index-1).getDistance());


            //Nicely formatted string~ the beauty of laziness
            itemToAppend = QString("From %1 -> %2 : Distance [%3]")
                    .arg(sourceStadium, destinationStadium, distanceBetween);
        }

        //Go ahead and add to the list widget
        ui->tripSummary_listWidget_tripPath->addItem(itemToAppend);
    }
}

/**
 * @brief TripSummary::clearData
 * Clears the list
 */
void TripSummary::clearData()
{
    ui->tripSummary_listWidget_tripPath->clear();
    ui->tripSummary_tableWidget_Purchases->clear();
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

    //assign id numbers
    int sourceID, destinationID;
    //Offset ID numbers by 1 to get actual positions in the vertexList inside Graph
    sourceID = db->GetStadiumID(stadiumList.at(0)) - 1;
    destinationID = db->GetStadiumID(stadiumList.at(stadiumList.size()-1)) - 1;

    //Call populateTripPath() to write to list
    populateTripPath(graphOfStadiums.findShortestPathTo(db, sourceID, destinationID));

}
