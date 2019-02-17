#ifndef BFEEDINGEVENT_H
#define BFEEDINGEVENT_H

#include "feedingevent.h"

class BFeedingEvent : public FeedingEvent
{
public:
    BFeedingEvent();
    PEvent clone();
};

#endif // BFEEDINGEVENT_H
