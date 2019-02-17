#ifndef FEEDINGEVENT_H
#define FEEDINGEVENT_H

#include "event.h"

class FeedingEvent : public Event
{
public:
    FeedingEvent();

    QString getShortDesc();
    QString getAlarmDesc();
    QString getNotfDesc();
};

#endif // FEEDINGEVENT_H
