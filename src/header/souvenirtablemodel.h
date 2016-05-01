#ifndef SOUVENIRTABLEMODEL_H
#define SOUVENIRTABLEMODEL_H

#include "database.h"
#include <QSqlTableModel>
#include <QObject>

class SouvenirTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    // fields in table souvenirs
    enum Fields
    {
        STADIUM_ID,
        NAME,
        PRICE
    };

    // Constructor
    SouvenirTableModel(QObject *parent, Database *db);
    SouvenirTableModel(QObject *parent, Database *db, int stadiumId);

    // Initialize model settings
    void Initialize(int stadiumId = -1);
};

#endif // SOUVENIRTABLEMODEL_H
