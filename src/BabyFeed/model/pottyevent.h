#ifndef POTTYEVENT_H
#define POTTYEVENT_H

#include "event.h"

class PottyEvent : public Event
{
public:
    static const QString ICON;

    PottyEvent();

    QString getShortDesc();
    QString getAlarmDesc();
    QString getNotfDesc();
    QString getIcon();
    PEvent clone();
    bool isRecurrentAble();
};

#endif // POTTYEVENT_H
