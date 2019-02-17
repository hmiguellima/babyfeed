#ifndef LFEEDINGEVENT_H
#define LFEEDINGEVENT_H

#include "feedingevent.h"

class LFeedingEvent : public FeedingEvent
{
public:
    LFeedingEvent();
    PEvent clone();
};

#endif // LFEEDINGEVENT_H
