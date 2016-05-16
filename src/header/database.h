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

  // Mutators
  /// Add a souvenir to a stadium's souvenir list
  bool AddSouvenir(QString stadiumName, QString itemName, double itemPrice);

  /// Add a Stadium to Stadium's data base
  bool AddStadium(QString stadiumName,QString teamName,QString address,QString phoneNumber,QString dateOpened,QString capacity,QString turfType,long revenue,QString leauge,QString typology);

  /// Add edges between vertecies to distances database
  bool AddDistance(int a,int b,long distance);
  // Accessors
  /// Retrieve a list of stadium names
  QStringList GetStadiumNames();

  /// Retrieve a stadium ID given the name
  int GetStadiumID(QString name);

  /// Retrieve the total amount of revenue from all stadiums.
  double GetTotalRevenues();

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
