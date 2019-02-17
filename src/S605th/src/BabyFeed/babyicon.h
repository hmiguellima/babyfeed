#ifndef BABYICON_H
#define BABYICON_H

#include <QWidget>
#include "baby.h"
#include <QComboBox>

namespace Ui {
    class BabyIcon;
}

class BabyIcon : public QWidget
{
    Q_OBJECT

public:
    explicit BabyIcon(Baby& baby, QWidget* parent = 0);
    ~BabyIcon();

    void setSelected(bool selected);
    bool isSelected();
    Baby& getBaby();

protected slots:
    void selectBaby();
    void updatePhoto(Baby &baby);

protected:
    virtual void paintEvent(QPaintEvent *);

private:
    Ui::BabyIcon *ui;
    Baby baby;
    bool selected;
    QComboBox *babyMenu;

private slots:
    void handleBabyMenuActivated(int index);
};

#endif // BABYICON_H
