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
