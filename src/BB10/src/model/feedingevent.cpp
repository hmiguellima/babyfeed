#include "feedingevent.h"
#include <QString>
#include <QDateTime>
#include "baby.h"

const QString FeedingEvent::ICON_LEFT="breastfeeding-left";
const QString FeedingEvent::ICON_BOTTLE="baby_bottle";
const QString FeedingEvent::ICON_RIGHT="breastfeeding-right";


FeedingEvent::FeedingEvent() : BabyEvent()
{
}

QString FeedingEvent::getShortDesc()
{
    QString eventData;
    int min;
    QDateTime endTime;

    if (getStartDate()>QDateTime::currentDateTime())
        eventData=QObject::tr("At: ")+getStartDate().toString("hh:mm");
    else
    {
        min=getDuration();
        endTime=getStartDate().addSecs(min*60);
        eventData=QObject::tr("End: ")+endTime.toString("hh:mm")+QObject::tr(", Min.: ")+QString::number(min);
    }

    return eventData;
}

QString FeedingEvent::getAlarmDesc()
{
    QString babyName=Baby::getBabyById(getBabyId()).getName();
    return QObject::tr("It's time to feed ")+babyName;
}


QString FeedingEvent::getNotfDesc()
{
    QString babyName=Baby::getBabyById(getBabyId()).getName();
    return QString(QObject::tr("%0 was fed at %1")).
            arg(babyName).
            arg(getStartDate().toString("hh:mm"));
}

QString FeedingEvent::getIcon()
{
    switch (type)
    {
        case BabyEvent::TYPE_LEFT_BREAST:
            return ICON_LEFT;
        case BabyEvent::TYPE_BOTTLE:
            return ICON_BOTTLE;
        case BabyEvent::TYPE_RIGHT_BREAST:
            return ICON_RIGHT;
    }
    return "";
}

bool FeedingEvent::hasDuration()
{
    return true;
}

PEvent FeedingEvent::clone()
{
    PEvent event=PEvent(new FeedingEvent());
    QString notes=getNotes();

    event->setNotes(notes);

    return event;
}
