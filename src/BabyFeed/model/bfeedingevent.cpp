#include "bfeedingevent.h"

BFeedingEvent::BFeedingEvent() : FeedingEvent()
{
    setType(Event::TYPE_BOTTLE);
}

PEvent BFeedingEvent::clone()
{
    PEvent event=PEvent(new BFeedingEvent());
    QString notes=getNotes();

    event->setNotes(notes);

    return event;
}

