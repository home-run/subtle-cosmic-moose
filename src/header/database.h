#ifndef DATABASE_H
#define DATABASE_H
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

  // Accessors
  /// Retrieve a list of stadium names
  QStringList GetStadiumNames();

  /// Retrieve a stadium ID given the name
  int GetStadiumID(QString name);

  ///Destructor
  ~Database();
};

#endif // DATABASE_H
