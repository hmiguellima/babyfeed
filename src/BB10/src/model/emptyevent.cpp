#include "emptyevent.h"

EmptyEvent::EmptyEvent()
{
}

QString EmptyEvent::getShortDesc()
{
    return QObject::tr("<No events>");
}

QString EmptyEvent::getAlarmDesc()
{
    return "";
}

QString EmptyEvent::getNotfDesc()
{
    return "";
}


bool EmptyEvent::isEmpty()
{
    return true;
}

QString EmptyEvent::getIcon()
{
    return "";
}

PEvent EmptyEvent::clone()
{
    return PEvent(new EmptyEvent());
}
