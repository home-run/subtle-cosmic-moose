#include "header/database.h"

/*!
 * \brief Database::Database
 * \param path Path to SQL Database file
 */
Database::Database(QString path, QString driver="QSQLITE") : QSqlDatabase(addDatabase(driver))
{
    setHostName("localhost");
    setDatabaseName(path);

    if(open())
    {
        qDebug() << "Database opened successfully";
    }
    else
    {
        qDebug() << this->lastError().text();
    }

    //  query.exec("PRAGMA foreign_keys = ON;");
}
