#ifndef RFEEDINGEVENT_H
#define RFEEDINGEVENT_H

#include "feedingevent.h"

class RFeedingEvent : public FeedingEvent
{
public:
    RFeedingEvent();
    PEvent clone();
};

#endif // RFEEDINGEVENT_H
