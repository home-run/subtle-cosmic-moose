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

    struct purchaseInfo{
        QString stadiumName;
        QString itemName;
        double  itemPrice;
        int     quantity;
    };

    QList<purchaseInfo> getPurchases();

public slots:
    void propagateStadiumList(QStringList stadiums);

private slots:
    void on_purchaseWindow_comboBox_selectStadium_currentIndexChanged(const QString &arg1);

    void on_purchaseWindow_tableView_souvenirList_doubleClicked(const QModelIndex &index);

    void on_purchaseWindow_tableWidget_shoppingCart_doubleClicked(const QModelIndex &index);

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    void initializeCartWidget();
    void initializeSouvenirView();
    Ui::PurchaseWindow *ui;
    SouvenirTableModel *souvenirModel;
    Database *db;
};

#endif // PURCHASEWINDOW_H
