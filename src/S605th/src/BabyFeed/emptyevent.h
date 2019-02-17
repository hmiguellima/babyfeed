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
    bool isEmpty();
};

#endif // EMPTYEVENT_H
