#include "babyicon.h"
#include "ui_babyicon.h"
#include "mainwindow.h"
#include <QPalette>
#include <QStyle>
#include <QStylePainter>
#include <QStyleOptionFocusRect>
#include <QString>
#include <QPixmap>
#include <QIcon>
#include <QImage>
#include "eventbus.h"


BabyIcon::BabyIcon(Baby &baby, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BabyIcon)
{
    ui->setupUi(this);
    this->baby=baby;

    babyMenu=new QComboBox(this);
    babyMenu->setVisible(false);
    babyMenu->addItem(tr("Edit"));
    babyMenu->addItem(tr("delete"));
    connect(babyMenu, SIGNAL(activated(int)), this, SLOT(handleBabyMenuActivated(int)));

    ui->fotoButton->setIcon(QIcon(QPixmap::fromImage(baby.getPhoto())));
    ui->fotoButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    ui->nameLabel->setText(baby.getName());
    connect(ui->fotoButton, SIGNAL(clicked()), this, SLOT(selectBaby()));
    setSelected(baby.isSelected());
    connect(EventBus::getInstance(), SIGNAL(babyUpdated(Baby&)), this, SLOT(updatePhoto(Baby&)));
}

void BabyIcon::paintEvent(QPaintEvent *)
{
    QStylePainter painter(this);
    QStyleOptionButton option;

    option.initFrom(this);


    if (!selected)
        painter.drawPrimitive(QStyle::PE_PanelButtonTool, option);
    else
        painter.drawPrimitive(QStyle::PE_FrameButtonTool, option);
}

void BabyIcon::selectBaby()
{
    if ( (baby.isSelected()) || (baby.getGender()==NewBaby) )
    {
        if (baby.getGender()==NewBaby)
            EventBus::getInstance()->fireShowBabyScreen(baby);
        else
            babyMenu->showPopup();
    }
    else
    {
        setSelected(true);
        EventBus::getInstance()->fireBabySelected(baby);
    }
}

BabyIcon::~BabyIcon()
{
    delete ui;
}

void BabyIcon::setSelected(bool selected)
{
    this->selected=selected;

    repaint();
}

bool BabyIcon::isSelected()
{
    return selected;
}

Baby& BabyIcon::getBaby()
{
    return baby;
}

void BabyIcon::updatePhoto(Baby &baby)
{
    if (this->baby.getId()==baby.getId())
        ui->fotoButton->setIcon(QIcon(QPixmap::fromImage(baby.getPhoto())));
}

void BabyIcon::handleBabyMenuActivated(int index)
{
    switch(index)
    {
    case 0:
        EventBus::getInstance()->fireShowBabyScreen(baby);
        break;
    case 1:
        baby.remove();
        EventBus::getInstance()->fireBabyDeleted(baby);
        break;
    }
}
