#include "babyicon.h"
#include "mainwindow.h"
#include <QString>
#include <QPixmap>
#include <QIcon>
#include <QImage>
#include <QMessageBox>
#include <QPushButton>
#include <QSizePolicy>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QStyle>
#include "model/eventbus.h"
#include <QSpacerItem>
#include <QSpacerItem>

BabyIcon::BabyIcon(Baby &baby, QWidget *parent) :
    QPushButton(parent)
{
    QHBoxLayout* hLayout=new QHBoxLayout();
    QVBoxLayout* vLayout=new QVBoxLayout();
    QSpacerItem* spacer=new QSpacerItem(14, 5);
    QFont ageFont;

    hLayout->setMargin(8);
    hLayout->setSpacing(5);
    vLayout->setSpacing(8);
    ageFont.setPointSize(6);

    setLayout(hLayout);
    babyFoto = new QLabel();
    babyFoto->setPixmap(QPixmap::fromImage(baby.getPhoto()));
    babyFoto->setFixedSize(QSize(133,100));
    hLayout->addWidget(babyFoto);
    hLayout->addLayout(vLayout);
    hLayout->addItem(spacer);

    babyName = new QLabel();
    babyName->setText(baby.getName());
    vLayout->addWidget(babyName);
    babyAge = new QLabel();
    babyAge->setText(baby.getAge());
    babyAge->setFont(ageFont);
    vLayout->addWidget(babyAge);
    babyMeasures=new QLabel();
    babyMeasures->setText(baby.getLastMeasures());
    babyMeasures->setFont(ageFont);
    vLayout->addWidget(babyMeasures);
    vLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));

    this->baby=baby;
    setCheckable(true);
    setChecked(baby.isSelected());

    babyMenu=new QComboBox(this);
    babyMenu->setVisible(false);
    babyMenu->addItem(tr("Edit"));
    babyMenu->addItem(tr("Delete"));
    connect(babyMenu, SIGNAL(activated(int)), this, SLOT(handleBabyMenuActivated(int)));

    connect(this, SIGNAL(clicked()), this, SLOT(selectBaby()));
    connect(EventBus::getInstance(), SIGNAL(babyUpdated(Baby&)), this, SLOT(updatePhoto(Baby&)));
}

void BabyIcon::selectBaby()
{
    if (isChecked())
    {
        if (baby.getGender()==NewBaby)
            EventBus::getInstance()->fireShowBabyScreen(baby);
        else
            babyMenu->showPopup();
    }
    else
    {
        setChecked(true);
        if (baby.getGender()!=NewBaby)
            EventBus::getInstance()->fireBabySelected(baby);
    }
}

BabyIcon::~BabyIcon()
{
}

Baby& BabyIcon::getBaby()
{
    return baby;
}

void BabyIcon::updatePhoto(Baby &baby)
{
    if (this->baby.getId()==baby.getId())
        babyFoto->setPixmap(QPixmap::fromImage(baby.getPhoto()));
}

void BabyIcon::handleBabyMenuActivated(int index)
{
    switch(index)
    {
    case 0:
        EventBus::getInstance()->fireShowBabyScreen(baby);
        break;
    case 1:
        int ret;

        ret=QMessageBox::warning(this, tr("BabyFeed"), tr("Remove baby file?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (ret==QMessageBox::Yes)
        {
            baby.remove();
            EventBus::getInstance()->fireBabyDeleted(baby);
        }
        break;
    }
}

void BabyIcon::updateMeasures()
{
    babyMeasures->setText(baby.getLastMeasures());
}
