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

int Database::getNumberOfStadiums() const
{
    QSqlQuery query;
    query.exec("select count(*) from stadiums");
    if(query.next())
    {
        if(DEBUG)
        { qDebug() << "Number of stadiums [ " << query.record().field(0).value().toInt() << " ]"; }
        return query.record().field(0).value().toInt();
    }
    return -1;
}

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
