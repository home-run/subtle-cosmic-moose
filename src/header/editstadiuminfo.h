#ifndef EDITSTADIUMINFO_H
#define EDITSTADIUMINFO_H

#include <QWidget>

namespace Ui {
class EditStadiumInfo;
}

class EditStadiumInfo : public QWidget
{
    Q_OBJECT

public:
    explicit EditStadiumInfo(QWidget *parent = 0);
    ~EditStadiumInfo();

private:
    Ui::EditStadiumInfo *ui;
};

#endif // EDITSTADIUMINFO_H
