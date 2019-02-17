#include "eventaddedevent.h"

EventAddedEvent::EventAddedEvent(Event event)
{
    this->event=event;
}

void EventAddedEvent::dispatch(EventAddedEventHandler *handler)
{
    handler->onEventAdded(event);
}

