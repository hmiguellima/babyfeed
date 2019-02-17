#include "event.h"
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include <QApplication>
#include <QMessageBox>
#include <QSqlError>
#include "emptyevent.h"
#include "lfeedingevent.h"
#include "bfeedingevent.h"
#include "rfeedingevent.h"
#include "medicineevent.h"
#include "pottyevent.h"
#include "baby.h"
#include "measureevent.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QScopedPointer>
#include <QDebug>
#include "model/calwrapper.h"

Event::Event()
{
    notes="";
    alarmNativeKey="";
    id=-1;
    checked=false;
    recurrenceId=-1;
    alarmNativeId=-1;
    weight=0;
    height=0;
    cephalic=0;
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
        sql="insert into FeedHistory (feed_id, feed_baby_id, feed_dateTime, feed_durationMin, feed_type, feed_notes, feed_recurrenceId, feed_alarmNativeId, feed_checked, feed_weight, feed_height, feed_cephalic, feed_alarmNativeKey) values("+
            QString::number(nextId)+","+
            QString::number(babyId)+","+
            "'"+startDate.toString("yyyy-MM-dd hh:mm")+"',"+
            QString::number(duration)+","+
            "'"+type+"',"+
            "'"+notes.replace("'", "")+"',"+
            QString::number(recurrenceId)+","+
            QString::number(alarmNativeId)+","+
            (checked?QString::number(1):QString::number(0))+","+
            QString::number(weight)+","+
            QString::number(height)+","+
            QString::number(cephalic)+","+
            "'"+alarmNativeKey+"'"
            ")";
    }
    else
        sql="update FeedHistory "
            "set feed_dateTime='"+startDate.toString("yyyy-MM-dd hh:mm")+"', "+
            "feed_durationMin="+QString::number(duration)+", "+
            "feed_type='"+type+"', "+
            "feed_notes='"+notes.replace("'", "")+"', "+
            "feed_checked="+(checked?QString::number(1):QString::number(0))+", "+
            "feed_weight="+QString::number(weight)+", "+
            "feed_height="+QString::number(height)+", "+
            "feed_cephalic="+QString::number(cephalic)+" "+
            "where feed_id="+QString::number(id);
    query.exec(sql);
    sql = "";
}


void Event::remove()
{
    QSqlQuery selectQuery;
    QSqlQuery deleteQuery;
    QString alarmId;

    if (recurrenceId!=-1)
    {
        selectQuery.exec("select distinct feed_alarmNativeKey from FeedHistory "
                         "where feed_alarmNativeKey <> '' and feed_recurrenceId="+QString::number(recurrenceId));

        while (selectQuery.next())
        {
            alarmId=selectQuery.value(0).toString();
            removeAlarm(alarmId, getStartDate().date());
        }

        deleteQuery.exec("delete from FeedHistory where feed_recurrenceId="+QString::number(recurrenceId));
    }
    else
    {
        deleteQuery.exec("delete from FeedHistory where feed_id="+QString::number(id));
        if (alarmNativeKey!="")
            removeAlarm(alarmNativeKey, getStartDate().date());
    }
}

QList<PEvent> Event::list(Baby &baby, QDate startDate, QDate endDate, QString filter)
{
    return Event::list(baby, startDate, endDate, filter, 0);
}

QList<PEvent> Event::list(Baby &baby, QDate startDate, QDate endDate, QString filter, int maxRecords)
{
    QList<PEvent> events;
    QSqlQuery query;
    int count=0;

    query.exec("select feed_id, feed_dateTime, feed_durationMin, feed_type, feed_notes, feed_recurrenceId, feed_alarmNativeId, feed_checked, feed_weight, feed_height, feed_cephalic, feed_alarmNativeKey from FeedHistory "
               "where feed_baby_id="+QString::number(baby.getId())+" "+
               "and feed_dateTime between '"+startDate.toString("yyyy-MM-dd")+"' and "
               "'"+endDate.addDays(1).toString("yyyy-MM-dd")+"' "
               +(filter.length()==0?"":"and "+filter+" ")+
               "order by feed_dateTime desc");

    while (query.next())
    {
        char type;
        Event *event;

        type=query.value(3).toString().toAscii().at(0);

        switch (type)
        {
        case TYPE_LEFT_BREAST:
            event=new LFeedingEvent();
            break;
        case TYPE_BOTTLE:
            event=new BFeedingEvent();
            break;
        case TYPE_RIGHT_BREAST:
            event=new RFeedingEvent();
            break;
        case TYPE_MEDICINE:
            event=new MedicineEvent();
            break;
        case TYPE_POTTY:
            event=new PottyEvent();
            break;
        case TYPE_MEASURE:
            event=new MeasureEvent();
            break;
        default:
            event=new EmptyEvent();
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
        event->setWeight(query.value(8).toInt());
        event->setHeight(query.value(9).toInt());
        event->setCephalic(query.value(10).toInt());
        event->setAlarmNativeKey(query.value(11).toString());

        events.append(PEvent(event));

        count++;
        if ( (count==maxRecords) && (maxRecords>0) )
            break;
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

void Event::setAlarm(QDateTime start, QDateTime end, QString message)
{
    QString alarmId;

    alarmId=CalWrapper::setAlarm(start, end, message);
    setAlarmNativeKey(alarmId);
}


void Event::removeAlarm(QString id, QDate date)
{
    qDebug() << "Event::removeAlarm:" << id;
    CalWrapper::removeAlarm(id, date);
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

void Event::deleteExpiredAlarms()
{
    QSqlQuery query;
    QSqlQuery updateQuery;
    QString currentDateTimeStr;
    QString alarmId;

    currentDateTimeStr=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");

    query.exec("select feed_alarmNativeKey, feed_dateTime from FeedHistory "
               "where feed_alarmNativeKey <> '' "
               "group by feed_alarmNativeKey "
               "having max(feed_dateTime) < '"+currentDateTimeStr+"' ");

    while (query.next())
    {
        alarmId=query.value(0).toString();
        removeAlarm(alarmId, query.value(1).toDate());
        updateQuery.exec("update FeedHistory set feed_alarmNativeKey='' "
                         "where feed_alarmNativeKey='"+alarmId+"'");
    }

}

QDate Event::getMinMeasurementEventDate(Baby &baby)
{
    QSqlQuery query;

    query.exec("select count(*) from FeedHistory "
               "where (feed_type = 'W') and feed_baby_id="+QString::number(baby.getId()));
    query.next();
    if (query.value(0).toInt()==0)
        return QDate::currentDate();

    query.exec("select min(feed_dateTime) from FeedHistory "
               "where (feed_type = 'W') and feed_baby_id="+QString::number(baby.getId()));
    query.next();
    return query.value(0).toDate();
}

QDate Event::getMaxMeasurementEventDate(Baby &baby)
{
    QSqlQuery query;

    query.exec("select count(*) from FeedHistory "
               "where (feed_type = 'W') and feed_baby_id="+QString::number(baby.getId()));
    query.next();
    if (query.value(0).toInt()==0)
        return QDate::currentDate();

    query.exec("select max(feed_dateTime) from FeedHistory "
               "where (feed_type = 'W') and feed_baby_id="+QString::number(baby.getId()));
    query.next();
    return query.value(0).toDate();
}

QDate Event::getMinFeedEventDate(Baby &baby)
{
    QSqlQuery query;

    query.exec("select count(*) from FeedHistory "
               "where (feed_type in ('L', 'B', 'R')) and feed_baby_id="+QString::number(baby.getId()));
    query.next();
    if (query.value(0).toInt()==0)
        return QDate::currentDate();

    query.exec("select min(feed_dateTime) from FeedHistory "
               "where (feed_type in ('L', 'B', 'R')) and feed_baby_id="+QString::number(baby.getId()));
    query.next();
    return query.value(0).toDate();
}

QDate Event::getMaxFeedEventDate(Baby &baby)
{
    QSqlQuery query;

    query.exec("select count(*) from FeedHistory "
               "where (feed_type in ('L', 'B', 'R')) and feed_baby_id="+QString::number(baby.getId()));
    query.next();
    if (query.value(0).toInt()==0)
        return QDate::currentDate();

    query.exec("select max(feed_dateTime) from FeedHistory "
               "where (feed_type in ('L', 'B', 'R')) and feed_baby_id="+QString::number(baby.getId()));
    query.next();
    return query.value(0).toDate();
}

void Event::setHeight(int height)
{
    this->height = height;
}

int Event::getHeight()
{
    return height;
}

void Event::setWeight(int weight)
{
    this->weight=weight;
}

int Event::getWeight()
{
    return weight;
}

void Event::setCephalic(int cephalic)
{
    this->cephalic=cephalic;
}

int Event::getCephalic()
{
    return cephalic;
}


bool Event::isRecurrentAble()
{
    return false;
}

bool Event::hasDuration()
{
    return false;
}

int Event::getTypeIndex(char type)
{
    switch (type) {
    case TYPE_LEFT_BREAST:
        return LEFT_BREAST;
    case TYPE_BOTTLE:
        return BOTTLE;
    case TYPE_RIGHT_BREAST:
        return RIGHT_BREAST;
    case TYPE_POTTY:
        return POTTY;
    case TYPE_MEDICINE:
        return MEDICINE;
    case TYPE_MEASURE:
        return MEASURE;
    }

    return 0;
}

char Event::getTypeFromIndex(int index)
{
    switch (index) {
    case LEFT_BREAST:
        return TYPE_LEFT_BREAST;
    case BOTTLE:
        return TYPE_BOTTLE;
    case RIGHT_BREAST:
        return TYPE_RIGHT_BREAST;
    case POTTY:
        return TYPE_POTTY;
    case MEDICINE:
        return TYPE_MEDICINE;
    case MEASURE:
        return TYPE_MEASURE;
    }

    return 0;
}

void Event::setAlarmNativeKey(QString key)
{
    alarmNativeKey=key;
}

QString Event::getAlarmNativeKey()
{
    return alarmNativeKey;
}

void Event::setTimerAlarm(QDateTime start, QString message)
{
    QScopedPointer<LFeedingEvent> event(new LFeedingEvent());
    event->setAlarm(start, start, message);
}

QString Event::getTypeName()
{
    switch (type) {
    case TYPE_LEFT_BREAST:
        return tr("Left breast");
    case TYPE_BOTTLE:
        return tr("Bottle");
    case TYPE_RIGHT_BREAST:
        return tr("Right breast");
    case TYPE_POTTY:
        return tr("Potty");
    case TYPE_MEDICINE:
        return tr("Medicine");
    case TYPE_MEASURE:
        return tr("Measurement");
    }
    return "";
}
