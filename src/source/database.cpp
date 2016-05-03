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
