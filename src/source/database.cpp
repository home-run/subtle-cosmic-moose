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

    //  We may or may not need this later on.
    //  This is for activating foreign key support.
    //  query.exec("PRAGMA foreign_keys = ON;");
}
