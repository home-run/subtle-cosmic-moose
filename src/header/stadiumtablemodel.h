#ifndef STADIUMTABLEMODEL_H
#define STADIUMTABLEMODEL_H
#include <QSqlTableModel>
#include <QObject>
#include "database.h"

class StadiumTableModel : public QSqlTableModel
{
    Q_OBJECT
public:

    // Fields in table stadiums
    enum Fields
    {
        ID,
        NAME,
        TEAM,
        ADDRESS,
        PHONE,
        DATE,
        CAPACITY,
        TURF,
        REVENUE,
        LEAGUE
    };

    // Constructor
    StadiumTableModel(QObject *parent, Database *db);

    // Initialize model settings
    void Initialize();

};

#endif // STADIUMTABLEMODEL_H
