#include "kineticscrollarea.h"
#include <QScrollBar>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QObjectList>

KineticScrollArea::KineticScrollArea(QWidget* parent, ScrollDir dir):
    QScrollArea(parent)
{
    this->dir=dir;
    scrollerContents=new QWidget(this);
    setWidget(scrollerContents);
    setWidgetResizable(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    if (dir==VerticalScrollDir)
    {
        layout=new QVBoxLayout(scrollerContents);
        spacer=new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    }
    else
    {
        layout=new QHBoxLayout(scrollerContents);
        spacer=new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    }

    layout->addItem(spacer);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    kineticScroller.setWidget(this);
}

KineticScrollArea::KineticScrollArea(QWidget *parent):
            QScrollArea(parent)
{
    setWidgetResizable(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    kineticScroller.setWidget(this);
}

KineticScrollArea::~KineticScrollArea()
{
}

void KineticScrollArea::addWidget(QWidget *widget)
{
    layout->removeItem(spacer);
    layout->insertWidget(layout->children().count()-1, widget);
    layout->addItem(spacer);
}

void KineticScrollArea::clearWidgets()
{
    QObject *object;
    QObjectList children;

    children=scrollerContents->children();

    foreach(object, children)
        if (object!=layout)
            delete object;
}
