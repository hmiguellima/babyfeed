#ifndef KINETICSCROLLAREA_H
#define KINETICSCROLLAREA_H

#include <QScrollArea>
#include <QWidget>
#include <QPoint>
#include <QBoxLayout>
#include "flickable/qscrollareakineticscroller.h"

class KineticScrollArea: public QScrollArea
{
public:
    enum ScrollDir
    {
        VerticalScrollDir,
        HorizontalScrollDir
    };

    KineticScrollArea(QWidget* parent, ScrollDir dir);
    KineticScrollArea(QWidget* parent);
    ~KineticScrollArea();
    void addWidget(QWidget* widget);
    void clearWidgets();

private:
    QWidget* scrollerContents;
    ScrollDir dir;
    QSpacerItem* spacer;
protected:
    QScrollAreaKineticScroller kineticScroller;
    QBoxLayout* layout;
};

#endif // KINETICSCROLLAREA_H
