#include "feedingevent.h"
#include <QApplication>
#include <QString>
#include <QDateTime>
#include "baby.h"

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
        eventData=QApplication::tr("End: ")+endTime.toString("hh:mm")+QApplication::tr(", Minutes: ")+QString::number(min);
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
            arg(QTime::currentTime().toString("hh:mm"));
}
