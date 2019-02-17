#ifndef MEASUREEVENT_H
#define MEASUREEVENT_H

#include "event.h"
#include <QString>
#include "baby.h"

class MeasureEvent : public BabyEvent
{
public:
    static const QString ICON;

    MeasureEvent();

    QString getShortDesc();
    QString getAlarmDesc();
    QString getNotfDesc();
    QString getIcon();
    PEvent clone();

    bool isRecurrentAble();
    static QString getLastMeasures(Baby &baby);

private:
};

#endif // MEASUREEVENT_H
