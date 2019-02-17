#ifndef FEEDINGEVENT_H
#define FEEDINGEVENT_H

#include "event.h"

class FeedingEvent : public Event
{
public:
    static const QString ICON_LEFT;
    static const QString ICON_BOTTLE;
    static const QString ICON_RIGHT;

    FeedingEvent();

    QString getShortDesc();
    QString getAlarmDesc();
    QString getNotfDesc();
    QString getIcon();
    PEvent clone();
    bool hasDuration();
};

#endif // FEEDINGEVENT_H
