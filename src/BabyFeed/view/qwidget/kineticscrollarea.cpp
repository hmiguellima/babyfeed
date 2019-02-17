#include "kineticscrollarea.h"
#include <QScrollBar>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QObjectList>
#include "qtkineticscroller/qtscroller.h"
#include <QFrame>

KineticScrollArea::KineticScrollArea(QWidget *parent):
            QScrollArea(parent)
{
    scrollerContents=new QWidget(this);
    scrollerContents->setAutoFillBackground(true);
    scrollerContents->setBackgroundRole(QPalette::Base);
    setWidget(scrollerContents);
    setWidgetResizable(true);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout=new QHBoxLayout();
    scrollerContents->setLayout(layout);
    spacer=new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addItem(spacer);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QtScroller::grabGesture(viewport(), QtScroller::LeftMouseButtonGesture);
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
    QWidget *widget;

    children=scrollerContents->children();

    foreach(object,children)
    {
        widget=dynamic_cast<QWidget*>(object);
        if (widget)
            widget->deleteLater();
    }
}
