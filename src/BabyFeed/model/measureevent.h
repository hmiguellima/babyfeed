#ifndef MEASUREEVENT_H
#define MEASUREEVENT_H

#include "event.h"
#include <QString>
#include <QLineEdit>
#include <QDoubleValidator>
#include "baby.h"

class MeasureEvent : public Event
{
public:
    static const QString ICON;

    MeasureEvent();

    QString getShortDesc();
    QString getAlarmDesc();
    QString getNotfDesc();
    QString getIcon();
    PEvent clone();
    QDoubleValidator* validator;

    bool isRecurrentAble();
    static QString getLastMeasures(Baby &baby);

private:
    QLineEdit* weightEdit;
    QLineEdit* heightEdit;
    QLineEdit* cephalicEdit;
};

#endif // MEASUREEVENT_H
