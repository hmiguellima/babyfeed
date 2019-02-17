#ifndef EMPTYEVENT_H
#define EMPTYEVENT_H

#include "event.h"

class EmptyEvent : public Event
{
public:
    EmptyEvent();

    QString getShortDesc();
    QString getAlarmDesc();
    QString getNotfDesc();
    QString getIcon();
    bool isEmpty();
    PEvent clone();
};

#endif // EMPTYEVENT_H
