#include "feedingevent.h"
#include <QApplication>
#include <QString>
#include <QDateTime>
#include "baby.h"

const QString FeedingEvent::ICON_LEFT="breastfeeding-left";
const QString FeedingEvent::ICON_BOTTLE="baby_bottle";
const QString FeedingEvent::ICON_RIGHT="breastfeeding-right";


FeedingEvent::FeedingEvent() : Event()
{
}

QString FeedingEvent::getShortDesc()
{
    QString eventData;
    int min;
    QDateTime endTime;

    if (getStartDate()>QDateTime::currentDateTime())
        eventData=QApplication::tr("At: ")+getStartDate().toString("hh:mm");
    else
    {
        min=getDuration();
        endTime=getStartDate().addSecs(min*60);
        eventData=QApplication::tr("End: ")+endTime.toString("hh:mm")+QApplication::tr(", Min.: ")+QString::number(min);
    }

    return eventData;
}

QString FeedingEvent::getAlarmDesc()
{
    QString babyName=Baby::getBabyById(getBabyId()).getName();
    return QApplication::tr("It's time to feed ")+babyName;
}


QString FeedingEvent::getNotfDesc()
{
    QString babyName=Baby::getBabyById(getBabyId()).getName();
    return QString(QApplication::tr("%0 was fed at %1")).
            arg(babyName).
            arg(getStartDate().toString("hh:mm"));
}

QString FeedingEvent::getIcon()
{
    switch (type)
    {
        case Event::TYPE_LEFT_BREAST:
            return ICON_LEFT;
        case Event::TYPE_BOTTLE:
            return ICON_BOTTLE;
        case Event::TYPE_RIGHT_BREAST:
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
