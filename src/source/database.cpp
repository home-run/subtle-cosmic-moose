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

QSqlQuery Database::getDistances()
{
    QSqlQuery query;
    query.exec("SELECT * FROM distances");

    qDebug() << "ID From [ " << query.value(1).toInt() << " ] ID to [ " << query.value(2).toInt() << " ] Distance [ " << query.value(3).toInt() << " ]";
    return query;
}
