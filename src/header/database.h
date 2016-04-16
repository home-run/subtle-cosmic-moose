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
  ///Destructor
  ~Database();
};

#endif // DATABASE_H
