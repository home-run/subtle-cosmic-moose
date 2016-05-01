#ifndef ADDSOUVENIR_H
#define ADDSOUVENIR_H

#include "database.h"
#include <QDialog>

namespace Ui {
class addsouvenir;
}

class addsouvenir : public QDialog
{
    Q_OBJECT

public:
    explicit addsouvenir(QWidget *parent = 0, Database *db = 0);
    ~addsouvenir();

private:
    Ui::addsouvenir *ui;
    Database *db;
};

#endif // ADDSOUVENIR_H
