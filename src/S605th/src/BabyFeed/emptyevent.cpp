#include "emptyevent.h"

EmptyEvent::EmptyEvent()
{
}

QString EmptyEvent::getShortDesc()
{
    return "<No events>";
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
