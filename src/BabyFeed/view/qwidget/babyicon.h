#ifndef BABYICON_H
#define BABYICON_H

#include <QWidget>
#include "model/baby.h"
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

class BabyIcon : public QPushButton
{
    Q_OBJECT

public:
    explicit BabyIcon(Baby& baby, QWidget* parent = 0);
    ~BabyIcon();

    void setSelected(bool selected);
    bool isSelected();
    Baby& getBaby();
    void updateMeasures();

public slots:
    void updatePhoto(Baby &baby);
    void selectBaby();

protected:

private:
    Baby baby;
    bool selected;
    QComboBox *babyMenu;
    //QString babyName;
    QLabel* babyFoto;
    QLabel* babyName;
    QLabel* babyAge;
    QLabel* babyMeasures;

private slots:
    void handleBabyMenuActivated(int index);
};

#endif // BABYICON_H
