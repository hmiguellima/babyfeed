#include "emptyevent.h"
#include <QApplication>

EmptyEvent::EmptyEvent()
{
}

QString EmptyEvent::getShortDesc()
{
    return QApplication::tr("<No events>");
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
