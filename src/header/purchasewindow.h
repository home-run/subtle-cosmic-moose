#ifndef PURCHASEWINDOW_H
#define PURCHASEWINDOW_H

#include <QWidget>
#include "database.h"
#include "souvenirtablemodel.h"

namespace Ui {
class PurchaseWindow;
}

class PurchaseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PurchaseWindow(QWidget *parent = 0, Database *db = 0);
    ~PurchaseWindow();

public slots:
    void propagateStadiumList(QStringList stadiums);

private slots:
    void on_purchaseWindow_comboBox_selectStadium_currentIndexChanged(const QString &arg1);

private:
    void initializeSouvenirView();
    Ui::PurchaseWindow *ui;
    SouvenirTableModel *souvenirModel;
    Database *db;
};

#endif // PURCHASEWINDOW_H
