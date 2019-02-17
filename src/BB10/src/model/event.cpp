#include "event.h"
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QString>
#include <QtSql/QSqlError>
#include "emptyevent.h"
#include "lfeedingevent.h"
#include "bfeedingevent.h"
#include "rfeedingevent.h"
#include "medicineevent.h"
#include "pottyevent.h"
#include "baby.h"
#include "measureevent.h"
#include <QScopedPointer>
#include <QDebug>
#include "model/calwrapper.h"

BabyEvent::BabyEvent()
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

int BabyEvent::getId()
{
    return id;
}

char BabyEvent::getType()
{
    return type;
}

void BabyEvent::setType(char type)
{
    this->type=type;
}

QDateTime BabyEvent::getStartDate()
{
    return startDate;
}

void BabyEvent::setStartDate(QDateTime startDate)
{
    this->startDate=startDate;
}

void BabyEvent::persist()
{
    QSqlQuery query;
    QString sql;
    int nextId=1;


    if (id==-1)
    {
        query.exec("select max(feed_id) from FeedHistory");
        if (query.next())
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


void BabyEvent::remove()
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

QList<PEvent> BabyEvent::list(Baby &baby, QDate startDate, QDate endDate, QString filter)
{
    return BabyEvent::list(baby, startDate, endDate, filter, 0);
}

QList<PEvent> BabyEvent::list(Baby &baby, QDate startDate, QDate endDate, QString filter, int maxRecords)
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
        BabyEvent *event;

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
            break;
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

int BabyEvent::getDuration()
{
    return duration;
}

void BabyEvent::setDuration(int duration)
{
    this->duration=duration;
}

bool BabyEvent::isEmpty()
{
    return false;
}

int BabyEvent::getBabyId()
{
    return babyId;
}

void BabyEvent::setBabyId(int babyId)
{
    this->babyId=babyId;
}

void BabyEvent::setRecurrenceId(int id)
{
    this->recurrenceId=id;
}

int BabyEvent::getRecurrenceId()
{
    return recurrenceId;
}

void BabyEvent::setAlarmNativeId(int alarmNativeId)
{
    this->alarmNativeId=alarmNativeId;
}

int BabyEvent::getAlarmNativeId()
{
    return alarmNativeId;
}

bool BabyEvent::isChecked()
{
    return checked;
}

void BabyEvent::setChecked(bool checked)
{
    this->checked=checked;
}

void BabyEvent::setAlarm(QDateTime start, QDateTime end, QString message)
{
    QString alarmId;

    alarmId=CalWrapper::setAlarm(start, end, message);
    setAlarmNativeKey(alarmId);
}


void BabyEvent::removeAlarm(QString id, QDate date)
{
    qDebug() << "Event::removeAlarm:" << id;
    CalWrapper::removeAlarm(id, date);
}

void BabyEvent::setNotes(QString &notes)
{
    this->notes=notes;
}

QString BabyEvent::getNotes()
{
    return notes;
}

int BabyEvent::getNextRecurrenceId()
{
    QSqlQuery query;

    query.exec("select max(feed_recurrenceId)+1 from FeedHistory");
    query.next();

    return query.value(0).toInt();
}

void BabyEvent::deleteExpiredAlarms()
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

QDate BabyEvent::getMinMeasurementEventDate(Baby &baby)
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

QDate BabyEvent::getMaxMeasurementEventDate(Baby &baby)
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

QDate BabyEvent::getMinFeedEventDate(Baby &baby)
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

QDate BabyEvent::getMaxFeedEventDate(Baby &baby)
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

void BabyEvent::setHeight(int height)
{
    this->height = height;
}

int BabyEvent::getHeight()
{
    return height;
}

void BabyEvent::setWeight(int weight)
{
    this->weight=weight;
}

int BabyEvent::getWeight()
{
    return weight;
}

void BabyEvent::setCephalic(int cephalic)
{
    this->cephalic=cephalic;
}

int BabyEvent::getCephalic()
{
    return cephalic;
}


bool BabyEvent::isRecurrentAble()
{
    return false;
}

bool BabyEvent::hasDuration()
{
    return false;
}

int BabyEvent::getTypeIndex(char type)
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

char BabyEvent::getTypeFromIndex(int index)
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

void BabyEvent::setAlarmNativeKey(QString key)
{
    alarmNativeKey=key;
}

QString BabyEvent::getAlarmNativeKey()
{
    return alarmNativeKey;
}

void BabyEvent::setTimerAlarm(QDateTime start, QString message)
{
    QScopedPointer<LFeedingEvent> event(new LFeedingEvent());
    event->setAlarm(start, start, message);
}

PEvent BabyEvent::getById(Baby &baby, int eventId) {
	QList<PEvent> eventList;

	eventList=BabyEvent::list(baby, QDate(1900, 1, 1), QDate(2100, 1, 1), QString("feed_id=%1").arg(eventId));

	return eventList.at(0);
}

QString BabyEvent::getTypeName()
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
