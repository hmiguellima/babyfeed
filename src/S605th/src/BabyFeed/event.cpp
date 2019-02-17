#include "event.h"
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include <QApplication>
#include <QMessageBox>
#include <QSqlError>
#include "emptyevent.h"
#include "feedingevent.h"
#include "medicineevent.h"
#include "baby.h"
#ifdef Q_OS_SYMBIAN
    #include "alarms/xqalarms.h"
#endif

Event::Event()
{
    notes="";
    id=-1;
    checked=false;
    recurrenceId=-1;
    alarmNativeId=-1;
}

int Event::getId()
{
    return id;
}

char Event::getType()
{
    return type;
}

void Event::setType(char type)
{
    this->type=type;
}

QDateTime Event::getStartDate()
{
    return startDate;
}

void Event::setStartDate(QDateTime startDate)
{
    this->startDate=startDate;
}

void Event::persist()
{
    QSqlQuery query;
    QString sql;
    int nextId=1;


    if (id==-1)
    {
        query.exec("select max(feed_id) from FeedHistory");
        if (query.next());
            nextId=query.value(0).toInt()+1;

        id=nextId;
        sql="insert into FeedHistory (feed_id, feed_baby_id, feed_dateTime, feed_durationMin, feed_type, feed_notes, feed_recurrenceId, feed_alarmNativeId, feed_checked) values("+
            QString::number(nextId)+","+
            QString::number(babyId)+","+
            "'"+startDate.toString("yyyy-MM-dd hh:mm")+"',"+
            QString::number(duration)+","+
            "'"+type+"',"+
            "'"+notes.replace("'", "")+"',"+
            QString::number(recurrenceId)+","+
            QString::number(alarmNativeId)+","+
            (checked?QString::number(1):QString::number(0))+
            ")";
    }
    else
        sql="update FeedHistory "
            "set feed_dateTime='"+startDate.toString("yyyy-MM-dd hh:mm")+"', "+
            "feed_durationMin="+QString::number(duration)+", "+
            "feed_type='"+type+"', "+
            "feed_notes='"+notes.replace("'", "")+"', "+
            "feed_checked="+(checked?QString::number(1):QString::number(0))+" "
            "where feed_id="+QString::number(id);
    query.exec(sql);
}


void Event::remove()
{
    QSqlQuery selectQuery;
    QSqlQuery deleteQuery;
    bool deleteAll=false;
    int feedId;
    int alarmId;

    if (recurrenceId!=-1)
        if (QMessageBox::question(0, QApplication::tr("BabyFeed"),
          QApplication::tr("This event is recursive, delete all?"),
          QMessageBox::Yes | QMessageBox::No, QMessageBox::No)==QMessageBox::Yes)
            deleteAll=true;

    if (deleteAll)
    {
        selectQuery.exec("select feed_id, feed_alarmNativeId from FeedHistory "
                   "where feed_recurrenceId="+QString::number(recurrenceId));

        while (selectQuery.next())
        {
            feedId=selectQuery.value(0).toInt();
            alarmId=selectQuery.value(1).toInt();
            deleteQuery.exec("delete from FeedHistory where feed_id="+QString::number(feedId));
            if (alarmId!=-1)
                removeAlarm(alarmId);
        }
    }
    else
    {
        deleteQuery.exec("delete from FeedHistory where feed_id="+QString::number(id));
        if (alarmNativeId!=-1)
            removeAlarm(alarmNativeId);
    }
}

QList<PEvent> Event::list(Baby &baby, QDate &startDate, QDate &endDate)
{
    QList<PEvent> events;
    QSqlQuery query;

    query.exec("select feed_id, feed_dateTime, feed_durationMin, feed_type, feed_notes, feed_recurrenceId, feed_alarmNativeId, feed_checked from FeedHistory "
               "where feed_baby_id="+QString::number(baby.getId())+" "+
               "and feed_dateTime between '"+startDate.toString("yyyy-MM-dd")+"' and "
               "'"+endDate.addDays(1).toString("yyyy-MM-dd")+"' "
               "order by feed_dateTime desc");

    while (query.next())
    {
        char type;
        Event *event;

        type=query.value(3).toString().toAscii().at(0);

        switch (type)
        {
        case 'L':
        case 'B':
        case 'R':
            event=new FeedingEvent();
            break;
        default:
            event=new MedicineEvent();
        }

        event->id=query.value(0).toInt();
        event->startDate=QDateTime::fromString(query.value(1).toString(), QString("yyyy-MM-dd hh:mm"));
        event->duration=query.value(2).toInt();
        event->type=type;
        event->notes=query.value(4).toString();
        event->setBabyId(baby.getId());
        event->recurrenceId=query.value(5).toInt();
        event->alarmNativeId=query.value(6).toInt();
        event->checked=query.value(7).toBool();

        events.append(PEvent(event));
    }
    if (events.size()==0)
        events.append(PEvent(new EmptyEvent()));

    return events;
}

int Event::getDuration()
{
    return duration;
}

void Event::setDuration(int duration)
{
    this->duration=duration;
}

bool Event::isEmpty()
{
    return false;
}

int Event::getBabyId()
{
    return babyId;
}

void Event::setBabyId(int babyId)
{
    this->babyId=babyId;
}

void Event::setRecurrenceId(int id)
{
    this->recurrenceId=id;
}

int Event::getRecurrenceId()
{
    return recurrenceId;
}

void Event::setAlarmNativeId(int alarmNativeId)
{
    this->alarmNativeId=alarmNativeId;
}

int Event::getAlarmNativeId()
{
    return alarmNativeId;
}

bool Event::isChecked()
{
    return checked;
}

void Event::setChecked(bool checked)
{
    this->checked=checked;
}

void Event::setAlarm(QDateTime dateTime, QString message)
{
#ifdef Q_OS_SYMBIAN
    XQAlarms alarmProvider;
    XQAlarm alarmData;

    alarmData.setExpiryTime(dateTime);
    alarmData.setMessage(message);
    alarmData.setRepeatDefinition(XQAlarm::RepeatOnce);

    if (!alarmProvider.addAlarm(alarmData))
        QMessageBox::information(0, "error", "Alarm not set!");

    setAlarmNativeId(alarmData.id());
#endif
}

void Event::removeAlarm(int id)
{
#ifdef Q_OS_SYMBIAN
    XQAlarms alarmProvider;

    alarmProvider.deleteAlarm(id);
#endif

}

void Event::setNotes(QString &notes)
{
    this->notes=notes;
}

QString Event::getNotes()
{
    return notes;
}

int Event::getNextRecurrenceId()
{
    QSqlQuery query;

    query.exec("select max(feed_recurrenceId)+1 from FeedHistory");
    query.next();

    return query.value(0).toInt();
}

