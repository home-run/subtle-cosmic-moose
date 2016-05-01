#ifndef DATABASE_H
#define DATABASE_H

#ifndef DEBUG
#define DEBUG 0
#endif

#include <QtSql>

/*!
 * \brief The Database class is a wrapper for QSqlDatabase
 */
class Database : public QSqlDatabase
{
public:
  ///Create database from specified db file and driver
  Database(QString path, QString driver);
  ///Destructor
  ~Database();

  /// Retrieve IDs and Distances
  QSqlQuery getEdges();

  /// Return the number of stadiums in the database
  int	getNumberOfStadiums() const;

  /// Get the query containing the ids and stadium names available in the database
  QSqlQuery getStadiumsNameId();
};

#endif // DATABASE_H
