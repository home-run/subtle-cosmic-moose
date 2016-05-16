#include "header/database.h"

/*!
 * \brief Database::Database
 * \param path Path to SQL Database file
 * \param driver QString identifier for the specific flavor of SQL we are using.
 */
Database::Database(QString path, QString driver) : QSqlDatabase(addDatabase(driver))
{
    setHostName("localhost");
    setDatabaseName(path);

    // If the database successfully opens
    if(open())
    {
        qDebug() << "Database opened successfully";
    }
    else
    {
        // Output the last error message from the database
        qDebug() << this->lastError().text();
    }

    //  This is for activating foreign key support.
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");
}

/**
 * @brief Database::getEdges
 * Method that executes a SQL query to grab all ids to, ids from and distances from
 * the distances table.
 * @return SQLquery containing the results of the
 */
QSqlQuery Database::getEdges()
{
    QSqlQuery query;
    query.exec("select * from distances");

    if(DEBUG)
    {
        while(query.next())
        {
            qDebug() << "ID From [ " <<  query.record().field("id_from").value().toInt()
                     << " ] ID to [ " << query.record().field("id_to").value().toInt()
                     << " ] Distance [ "
                     << query.record().field("distance").value().toInt() << " ]";
        }
    }
    return query;
}

/**
 * @brief Database::getNumberOfStadiums
 * Method executes a sql query to get the total number of stadiums in the database.
 * @return int value # of stadiums
 */
int Database::getNumberOfStadiums() const
{
    QSqlQuery query;
    query.exec("select count(*) from stadiums;");
    if(query.next())
    {
        if(DEBUG)
        { qDebug() << "Number of stadiums [ " << query.record().field(0).value().toInt() << " ]"; }
        return query.record().field(0).value().toInt();
    }
    return -1;
}
/**
 * @brief Database::getStadiumsNameId
 * Get the name, and ID of each of the stadiums from the database and order the results
 * by id, descending order.
 * @return SQLQuery containing the results from the exeuction
 */
QSqlQuery Database::getStadiumsNameId()
{
    QSqlQuery query;

    query.exec("select id, name from stadiums order by id");
        if(DEBUG)
        {
            QSqlQuery debug_query;
            debug_query = query;
            while(debug_query.next())
            {
                qDebug() << "ID [ " << debug_query.record().field("id").value().toInt() << " ] - Name [ " << debug_query.record().field("name").value().toString() << " ]";
            }
        }

    return query;
}
/**
 * @brief Database::AddSouvenir
 * Add a souvenir to a certain stadium's souvenir list given the stadium's name.
 * @param stadiumName The stadium name
 * @param itemName The item name
 * @param itemPrice The item price
 * @return true if it worked
 */
bool Database::AddSouvenir(QString stadiumName, QString itemName, double itemPrice)
{
    QSqlQuery query;
    query.prepare("INSERT INTO souvenirs (stadium_id, name, price) "
                  "VALUES (:id, :name, :price)");
    int id = GetStadiumID(stadiumName);
    qDebug() << "stadium id: " << id;
    if(id > -1)
    {
        query.bindValue(":id", id);
        query.bindValue(":name", itemName);
        query.bindValue(":price", itemPrice);
        if(query.exec()){
            return true;
        }
        else
        {
            qDebug() << this->lastError().text();
            return false;
        }
    }
    qDebug() << "That stadium does not exist!";
    return false;
}
/**
 * @brief Database::AddStadium
 * Adds new Stadium to the data base with the following attributes.
 * @param stadiumName
 * @param teamName
 * @param address
 * @param phoneNumber
 * @param dateOpened
 * @param capacity
 * @param turfType
 * @param revenue
 * @param leauge
 * @param typology
 * @return true if it worked else false
 */
bool Database::AddStadium(QString stadiumName,QString teamName,QString address,
                          QString phoneNumber,QString dateOpened,QString capacity,QString turfType,
                          long revenue,QString leauge,QString typology)
{
    QSqlQuery query;
    query.prepare("INSERT INTO stadiums(name,team,address,phone,date,capacity,turf,revenue,league,typology)"
                  "VALUES (:name,:team,:address,:phone,:date,:capacity,:turf,:revenue,:league,:typology)");

        query.bindValue(":name", stadiumName);
        query.bindValue(":team", teamName);
        query.bindValue(":address", address);
        query.bindValue(":phone", phoneNumber);
        query.bindValue(":date", dateOpened);
        query.bindValue(":capacity", capacity);
        query.bindValue(":turf", turfType);
        query.bindValue(":revenue", QString::number(revenue));
        query.bindValue(":league", leauge);
        query.bindValue(":typology", typology);
        if(query.exec()){
            return true;
        }

            qDebug() << query.lastError().text();
            return false;
}
/**
 * @brief Database::AddDistance
 * Adds new distacne between two vertecies
 * @param a starting vertex
 * @param b ending vertex
 * @param distance weight of the edge
 * @return true if it worked else false
 */
bool Database::AddDistance(int a,int b,long distance)
{
    QSqlQuery query;
    query.prepare("INSERT INTO distances(id_from,id_to,distance) Values(:id_from,:id_to,:distance)");

        query.bindValue(":id_from", a);
        query.bindValue(":id_to", b);
        query.bindValue(":distance", QString::number(distance));
        if(query.exec()){
            return true;
        }

            qDebug() << query.lastError().text();
            return false;
}
/**
 * @brief Database::AddRevenue
 * Add amount to revenue attribute in stadiums table
 * @param id stadiums id
 * @param revenue of the stadium
 * @return
 */
bool Database::AddRevenue(int id, double revenue)
{
    QSqlQuery query;
    query.prepare("select revenue from stadiums where id = :id");
    query.bindValue(":id", id);
    if(query.exec()){
        if(query.next()){
            int originalRev = query.record().field("revenue").value().toDouble();
            query.clear();
            query.prepare("update stadiums set revenue = :newRev where id = :id");
            int newRev = originalRev + revenue;
            query.bindValue(":newRev", newRev);
            query.bindValue(":id", id);
            return query.exec();
        }
        else
        {
            qDebug() << query.lastError().text();
            return false;
        }
    }
    else
    {
        qDebug() << query.lastError().text();
        return false;
    }
}

/**
 * @brief Database::GetStadiumNames
 * Retrieve a list of stadium names.
 * @return names a list of stadium names
 */
QStringList Database::GetStadiumNames()
{
    QSqlQuery query;
    QStringList names;
    if(query.exec("select name from stadiums;")){
        while(query.next()){
            names.append(query.record().field("name").value().toString());
        }
    }
    else
    {
        qDebug() << this->lastError().text();
    }
    return names;
}

/**
 * @brief Database::GetStadiumID
 * Retrieve a stadium's unique ID given its name
 * @param name the stadium name
 * @return the stadium ID
 */
int Database::GetStadiumID(QString name)
{
    QSqlQuery query;
    query.prepare("select id from stadiums where name = :name");
    query.bindValue(":name", name);

    if(query.exec()){
        if(query.next()){
            return query.record().field("id").value().toInt();
        }
    }
    else
    {
        qDebug() << this->lastError().text();
    }

    // it didn't work
    return -1;
}

/**
 * @brief getRevenue
 * stadiums revenue
 * @param id stadium
 * @return
 */
double Database::GetRevenue(int id)
{
    QSqlQuery query;
    query.prepare("select revenue froms stadiums where id = :id");
    query.bindValue(":id", id);
    if(query.exec()){
        if(query.next()){
            return query.record().field("revenue").value().toDouble();
        }
        else
        {
            qDebug() << query.lastError().text();
            return -1;
        }
    }
    else
    {
        qDebug() << query.lastError().text();
        return -1;
    }
}
