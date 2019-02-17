#include "rfeedingevent.h"

RFeedingEvent::RFeedingEvent() : FeedingEvent()
{
    setType(Event::TYPE_RIGHT_BREAST);
}

PEvent RFeedingEvent::clone()
{
    PEvent event=PEvent(new RFeedingEvent());
    QString notes=getNotes();

    event->setNotes(notes);
    return event;
}
