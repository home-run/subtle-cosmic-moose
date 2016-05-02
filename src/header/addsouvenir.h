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
    explicit addsouvenir(QWidget *parent = 0, Database *db = 0, QString stadiumName = "null");
    ~addsouvenir();

signals:
    void refreshModels();

private slots:
    void on_addSouvenir_confirmation_buttonBox_accepted();

    void on_addSouvenir_confirmation_buttonBox_rejected();

private:
    Ui::addsouvenir *ui;
    QString stadiumName;
    Database *db;
};

#endif // ADDSOUVENIR_H
