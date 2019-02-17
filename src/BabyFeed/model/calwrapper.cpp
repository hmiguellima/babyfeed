#include "calwrapper.h"
#if defined(MEEGO_VERSION)
    #include "mkcal/extendedcalendar.h"
    #include "mkcal/extendedstorage.h"
    #include "mkcal/notebook.h"
    #include "kcalcoren/event.h"
    #include "kcalcoren/alarm.h"
    #include "kcalcoren/kdatetime.h"
    #include "kcalcoren/duration.h"
#endif
#include <QSharedPointer>
#include <QLatin1String>
#include <QDebug>

#if defined(MEEGO_VERSION)
    using namespace KCalCore;
    using namespace mKCal;
#endif

#if defined(SYMBIAN_VERSION)
    #include <QOrganizerManager>
    #include <QOrganizerItem>
    #include <QOrganizerTodo>
    #include <QOrganizerItemReminder>
    #include <QOrganizerItemId>

    using namespace QtMobility;
#endif

CalWrapper::CalWrapper()
{
}

QString CalWrapper::setAlarm(QDateTime start, QDateTime end, QString message)
{
#if defined(MEEGO_VERSION)
    ExtendedCalendar::Ptr calendar = ExtendedCalendar::Ptr ( new ExtendedCalendar( KDateTime::Spec::LocalZone() ) );
    ExtendedStorage::Ptr storage = calendar->defaultStorage(calendar);
    Event::Ptr event;
    Alarm::Ptr alarm;

    storage->open();
    storage->load(start.date(), end.date());

    event=Event::Ptr(new Event());
    event->setDtStart(KDateTime(start));
    event->setDescription(message);
    event->setSummary(message);

    alarm=Alarm::Ptr(new Alarm(event.data()));
    alarm->setDisplayAlarm(message);
    alarm->setEnabled(true);
    alarm->setRepeatCount(1);
    alarm->setStartOffset(Duration(0));
    alarm->setTime(KDateTime(start));
    alarm->setEndOffset(Duration(0));

    event->addAlarm(alarm);


    calendar->addEvent(event, "11111111-2222-3333-4444-555555555555");
    calendar->save();

    storage->save();
    storage->close();

    qDebug() << "BabyFeed:Alarm set";
    return event->uid();
#endif

#if defined(SYMBIAN_VERSION)
    QOrganizerManager manager;
    QOrganizerCollectionId defaultCollectionId = manager.defaultCollection().id();
    QOrganizerItem item;
    QOrganizerEventTime timeRange;
    QOrganizerItemReminder reminder;

    item.setType(QOrganizerItemType::TypeEvent);
    item.setDescription(message);
    item.setDisplayLabel(message);

    timeRange.setStartDateTime(start);
    timeRange.setEndDateTime(end);
    item.saveDetail(&timeRange);

    item.setCollectionId(defaultCollectionId);

    reminder.setSecondsBeforeStart(0);

    if (!item.saveDetail(&reminder)) {
        qDebug() << "Error adding reminder to event:" << QString::number(manager.error());
        return "";
    }

    if (manager.saveItem(&item))
        return item.id().toString();
    else
    {
        qDebug() << "Error saving event to calendar:" << QString::number(manager.error());
        return "";
    }
#endif
}

void CalWrapper::removeAlarm(QString key, QDate date)
{
#if defined(MEEGO_VERSION)
    ExtendedCalendar::Ptr calendar = ExtendedCalendar::Ptr ( new ExtendedCalendar( KDateTime::Spec::LocalZone() ) );
    ExtendedStorage::Ptr storage = calendar->defaultStorage(calendar);
    Event::Ptr event;

    storage->open();
    storage->load(date.addDays(-15), date.addDays(15));

    event=calendar->event(key);
    if (event.data()==NULL)
        qDebug() << "CalWrapper::removeAlarm:Event doesnt exist";
    else
    {
        calendar->deleteEvent(event);
        calendar->save();
        storage->save();

        qDebug() << "BabyFeed:Alarm removed";
    }

    storage->close();
#endif

#if defined(SYMBIAN_VERSION)
    QOrganizerManager manager;

    manager.removeItem(QOrganizerItemId::fromString(key));
#endif
}
