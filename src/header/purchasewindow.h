#ifndef PURCHASEWINDOW_H
#define PURCHASEWINDOW_H

#include <QWidget>

namespace Ui {
class PurchaseWindow;
}

class PurchaseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PurchaseWindow(QWidget *parent = 0);
    ~PurchaseWindow();

private:
    Ui::PurchaseWindow *ui;
};

#endif // PURCHASEWINDOW_H
