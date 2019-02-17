#include "lfeedingevent.h"

LFeedingEvent::LFeedingEvent() : FeedingEvent()
{
    setType(FeedingEvent::TYPE_LEFT_BREAST);
}

PEvent LFeedingEvent::clone()
{
    PEvent event=PEvent(new LFeedingEvent());
    QString notes=getNotes();

    event->setNotes(notes);

    return event;
}
