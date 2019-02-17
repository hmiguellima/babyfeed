#ifndef KINETICSCROLLAREA_H
#define KINETICSCROLLAREA_H

#include <QScrollArea>
#include <QWidget>
#include <QPoint>
#include <QBoxLayout>

class KineticScrollArea: public QScrollArea
{
    Q_OBJECT
public:
    KineticScrollArea(QWidget* parent);
    ~KineticScrollArea();
    void addWidget(QWidget* widget);
    void clearWidgets();

    QWidget* scrollerContents;

protected:
    QBoxLayout* layout;

private:
    QSpacerItem* spacer;
};

#endif // KINETICSCROLLAREA_H
