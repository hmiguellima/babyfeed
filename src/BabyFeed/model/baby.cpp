#include "baby.h"
#include <QApplication>
#include <QIcon>
#include <QPixmap>
#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include <QByteArray>
#include <QBuffer>
#include <QSize>
#include <QFile>
#include "eventbus.h"
#include <QMessageBox>
#include <QSqlError>
#include "contactsmodel.h"
#include <QStringList>
#include "global.h"
#include <QDebug>
#include "measureevent.h"
#include <QContactPhoneNumber>
#include <QMessage>
#include <QMessageService>
#include <QMessageAddress>
#include "model/contactsmodel.h"
#include <QDir>

using namespace QtMobility;

class MessageServiceWrapper : public QObject
{
public:
    MessageServiceWrapper()
    {
        _service=NULL;
    }

    QMessageService* getService()
    {
        if (_service==NULL)
            _service=new QMessageService(this);
        return _service;
    }

private:
    QMessageService* _service;
};

MessageServiceWrapper smsService;

BabyData::BabyData()
{
    name="";
    selected=true;
    id=-1;
    feedAlarmActive=true;
    timeBetweenFeeds=120;
}

BabyData::BabyData(const BabyData &other) : QSharedData(other)
{
    id=other.id;
    birthDate=other.birthDate;
    gender=other.gender;
    name=other.name;
    selected=other.selected;
    feedAlarmActive=other.feedAlarmActive;
    timeBetweenFeeds=other.timeBetweenFeeds;
    notifications=other.notifications;
    oldNotifications=other.oldNotifications;
}

BabyData::~BabyData()
{
}

Baby::Baby()
{
    data=new BabyData();
}

Baby::~Baby()
{
}

QString Baby::getName()
{
    return data->name;
}

QDateTime Baby::getBirthDate()
{
    return data->birthDate;
}

Gender Baby::getGender()
{
    return data->gender;
}

void Baby::setBirthDate(QDateTime date)
{
    data->birthDate=date;
}

void Baby::setName(QString name)
{
    data->name=name;
}

void Baby::setGender(Gender gender)
{
    data->gender=gender;
}

Baby Baby::getBabyFromQuery(QSqlQuery *query)
{
    Baby baby;
    QImage photo;
    int test;

    test=query->value(0).toInt();
    baby.setId(test);
    test=baby.getId();
    baby.setName(query->value(1).toString());
    baby.setBirthDate(query->value(2).toDateTime());
    if (query->value(3).toString()=="B")
        baby.setGender(Boy);
    else
        baby.setGender(Girl);
    baby.setSelected(query->value(4).toBool());
    baby.setTimeBetweenFeeds(query->value(5).toInt());
    baby.setFeedAlarmActive(query->value(6).toBool());

    baby.loadNotifications();

    return baby;
}

QString Baby::fields()
{
    return "baby_id, baby_name, baby_birthDate, baby_gender, baby_selected, baby_timeBetweenFeeds, baby_feedAlarmActive";
}

QList<Baby> Baby::list()
{
    QList<Baby> babyList;
    QSqlQuery query;
    int test;

    query.exec("select "+fields()+" from Baby order by baby_id");
    while (query.next())
    {
        test=query.value(0).toInt();
        babyList.append(Baby::getBabyFromQuery(&query));
    }

    return babyList;
}

Baby Baby::getSelectedBaby()
{
    QSqlQuery query;

    query.exec("select "+fields()+" from Baby "
               "where baby_selected=1 "
               "order by baby_id");
    query.next();
    return Baby::getBabyFromQuery(&query);

}

QString Baby::getPhotoFileName(Baby &baby)
{
    QString path;

    path=appDataPath+"/"+QString::number(baby.getId())+".jpg";

    qDebug() << "getPhotoFileName:"+path;
    return path;
}

QString Baby::getPhotoUri(Baby &baby)
{
    QString path;

#if defined(MEEGO_VERSION)
    path="file://"+appDataPath+"/"+QString::number(baby.getId())+".jpg";
#else
    path="file:///"+appDataPath+"/"+QString::number(baby.getId())+".jpg";
#endif

    qDebug() << "getPhotoUri:"+path;

    return path;
}

bool Baby::hasPhoto(Baby &baby)
{
    return QFile::exists(Baby::getPhotoFileName(baby));
}

int Baby::getId()
{
    return data->id;
}

void Baby::setId(int id)
{
    data->id=id;
}

bool Baby::isSelected()
{
    return data->selected;
}

void Baby::setSelected(bool selected)
{
    data->selected=selected;
}

void Baby::persistSelected(bool selected)
{
    QSqlQuery query;

    data->selected=selected;
    if (data->id!=-1)
    {
        query.prepare("update Baby "
                      "set baby_selected=:baby_selected "
                      "where baby_id="+QString::number(data->id));
        query.bindValue(":baby_selected", QVariant(selected));
        query.exec();
    }
}

void Baby::persist()
{
    QSqlQuery query;
    int nextId=1;


    if (data->id==-1)
    {
        query.exec("select max(baby_id) from Baby");
        if (query.next());
            nextId=query.value(0).toInt()+1;
        data->id=nextId;
        query.prepare("insert into Baby (baby_id, baby_name, baby_birthDate, baby_gender, baby_selected, baby_timeBetweenFeeds, baby_feedAlarmActive) "
                      " values (:baby_id,:baby_name,:baby_birthDate,:baby_gender,:baby_selected,:baby_timeBetweenFeeds,:baby_feedAlarmActive)");
        query.bindValue(":baby_id", QVariant(data->id));
    }
    else
        query.prepare("update Baby "
                      "set baby_name=:baby_name,"
                      "baby_birthDate=:baby_birthDate,"
                      "baby_gender=:baby_gender,"
                      "baby_selected=:baby_selected, "
                      "baby_timeBetweenFeeds=:baby_timeBetweenFeeds, "
                      "baby_feedAlarmActive=:baby_feedAlarmActive "
                      "where baby_id="+QString::number(data->id));


    query.bindValue(":baby_name", QVariant(getName()));
    query.bindValue(":baby_birthDate", QVariant(getBirthDate()));
    if (getGender()==Boy)
        query.bindValue(":baby_gender", QVariant("B"));
    else
        query.bindValue(":baby_gender", QVariant("G"));
    query.bindValue(":baby_selected", QVariant(isSelected()));
    query.bindValue(":baby_timeBetweenFeeds", QVariant(getTimeBetweenFeeds()));
    query.bindValue(":baby_feedAlarmActive", QVariant(isFeedAlarmActive()));
    query.exec();

    syncNotifications();
}

void Baby::remove()
{
    QSqlQuery query;
    QString alarmId;
    QDate alarmDate;

    query.exec("delete from Baby where baby_id="+QString::number(getId()));
    query.exec("delete from Notification where notf_baby_id="+QString::number(getId()));

    query.exec("select distinct feed_alarmNativeKey, feed_dateTime from FeedHistory "
               "where feed_alarmNativeKey <> '' and feed_baby_id="+QString::number(getId()));

    while (query.next())
    {
        alarmId=query.value(0).toString();
        alarmDate=query.value(1).toDate();
        Event::removeAlarm(alarmId, alarmDate);
    }

    query.exec("delete from FeedHistory where feed_baby_id="+QString::number(getId()));

    QFile::remove(getPhotoFileName(*this));
}

QList<PEvent> Baby::listEvents(QDate &startDate, QDate &endDate, QString filter)
{
    return Event::list(*this, startDate, endDate, filter);
}

QList<PEvent> Baby::listEvents(QDate &startDate, QDate &endDate)
{
    return Event::list(*this, startDate, endDate, "");
}

QList<PEvent> Baby::listFeedEvents(QDate &startDate, QDate &endDate)
{
    return Event::list(*this, startDate, endDate, "(feed_type in ('L', 'B', 'R'))");
}

QList<PEvent> Baby::listMeasureEvents(QDate &startDate, QDate &endDate)
{
    return Event::list(*this, startDate, endDate, "(feed_type in ('W'))");
}

QList<PEvent> Baby::getLastMeasureEvent()
{
    return Event::list(*this, QDate(1900, 1, 1), QDate(2200, 1, 1), "(feed_type in ('W'))", 1);
}

void Baby::setFeedAlarmActive(bool active)
{
    data->feedAlarmActive=active;
}

bool Baby::isFeedAlarmActive()
{
    return data->feedAlarmActive;
}

void Baby::setTimeBetweenFeeds(int time)
{
    data->timeBetweenFeeds=time;
}

int Baby::getTimeBetweenFeeds()
{
    return data->timeBetweenFeeds;
}

void Baby::addNotification(QString contactKey, char type)
{
    Notification notification;

    notification.setContact(contactKey);
    notification.setType(type);

    data->notifications.append(notification);
}

void Baby::removeNotification(QString contactKey)
{
    Notification notification;
    bool found=false;

    foreach(notification, data->notifications)
    {
        if (notification.getContact()==contactKey) {
            found=true;
            break;
        }
    }

    if (found)
        data->notifications.removeOne(notification);
}

void Baby::loadNotifications()
{
    QSqlQuery query;

    query.exec("select notf_id, notf_type, notf_contact from Notification "
               "where  notf_baby_id="+QString::number(data->id));

    data->notifications.clear();
    data->oldNotifications.clear();

    while (query.next())
    {
        Notification notf(query.value(0).toInt());

        notf.setType(query.value(1).toString().toAscii().at(0));
        notf.setContact(query.value(2).toString());

        data->notifications.append(notf);
        data->oldNotifications.append(notf);
    }
}


QSet<QString> Baby::getNotfContactKeys()
{
    Notification notf;
    QSet<QString> contactIds;

    foreach(notf,data->notifications)
    {
        contactIds.insert(notf.getContact());
    }

    return contactIds;
}

char Baby::getNotificationType(QString contactKey)
{
    Notification notf;

    foreach(notf,data->notifications)
    {
        if (notf.getContact()==contactKey)
            return notf.getType();
    }

    return 0;
}

void Baby::updateNotfication(QString contactKey, char type)
{
    Notification notification;
    bool found=false;

    foreach(notification, data->notifications)
    {
        if (notification.getContact()==contactKey) {
            found=true;
            break;
        }
    }

    if (found)
        notification.setType(type);
    else
        addNotification(contactKey, type);
}

void Baby::syncNotifications()
{
    Notification notf;
    QSqlQuery query;
    int newId;

    foreach(notf,data->oldNotifications)
    {
        if (!data->notifications.contains(notf))
            query.exec("delete from Notification where notf_id="+QString::number(notf.getId()));
    }

    foreach(notf,data->notifications)
    {
        if (!data->oldNotifications.contains(notf))
        {
            query.exec("select max(notf_id) from Notification");
            query.next();
            newId=query.value(0).toInt()+1;

            query.clear();
            query.prepare("insert into Notification (notf_id, notf_type, notf_contact, notf_baby_id) "
                       "values (:id,:type,:contact,:baby)");
            query.bindValue(":id", newId);
            query.bindValue(":type", QString(notf.getType()));
            query.bindValue(":contact", notf.getContact());
            query.bindValue(":baby", getId());
            query.exec();

            notf.setId(newId);
        }
        else
            query.exec(QString("update Notification set notf_type='%0' where notf_id=%1").arg(QString(notf.getType())).arg(notf.getId()));
    }

    data->oldNotifications=data->notifications;
}

Baby Baby::getBabyById(int id)
{
    QSqlQuery query;

    query.exec("select "+fields()+" from Baby "
               "where baby_id="+QString::number(id));
    query.next();
    return Baby::getBabyFromQuery(&query);
}

bool Baby::notifyEvent(PEvent &event, ContactsModel* contactsModel)
{
    Notification notf;
    QString phone;
    QStringList phoneList;
    QMessageAddressList toList;
    QMessage message;

    foreach(notf, data->notifications)
    {
        if (  ( (notf.getType()=='F') && ( (event->getType()=='L') || (event->getType()=='B') || (event->getType()=='R') ) ) ||
              (notf.getType()==event->getType()) ||
              (notf.getType()=='B') )
        {
            phone=contactsModel->getContactPhone(notf.getContact());
            phoneList << phone;
        }
    }

    if (phoneList.count()>0)
    {
        foreach(phone, phoneList)
        {
            QMessageAddress address;

            address.setAddressee(phone);
            address.setType(QMessageAddress::Phone);
            toList.append(address);
        }
        message.setTo(toList);
        message.setType(QtMobility::QMessage::Sms);
        message.setBody(event->getNotfDesc());
        message.setParentAccountId(QMessageAccount::defaultAccount(QMessage::Sms));

        if (smsService.getService()->send(message))
            qDebug() << "Message sent";
        else
            qDebug() << "Message not sent:error:" << smsService.getService()->error();


        return true;
    }
    else
        return false;
}

QDate Baby::getMinFeedEventDate()
{
    return Event::getMinFeedEventDate(*this);
}

QDate Baby::getMaxFeedEventDate()
{
    return Event::getMaxFeedEventDate(*this);
}

QString Baby::getAge()
{
    QDate birthDate=getBirthDate().date();
    QDate today=QDate::currentDate();
    int months=0;
    int weeks;
    int days;

    months=(today.year()-birthDate.year())*12+(today.month()-birthDate.month());

    if ( (today.day() < birthDate.day()) )
        months--;

    if (months > 0)
    {
        if (months<12)
            return QApplication::tr("%0 month(s)").arg(months);
        else
            if (months%12==0)
                return QApplication::tr("%0 year(s)").arg(months/12);
            else
                return QApplication::tr("%0 year(s) and %1 month(s)").arg(months/12).arg(months % 12);
    }
    else
    {
        today = QDate::currentDate();
        days=birthDate.daysTo(today);
        weeks=days/7;
        if (weeks > 0)
            return QApplication::tr("%0 week(s) and %1 day(s)").arg(weeks).arg(days % 7);
        else
            return QApplication::tr("%0 day(s)").arg(days);
    }


}

QDate Baby::getMinMeasurementEventDate()
{
    return Event::getMinMeasurementEventDate(*this);
}

QDate Baby::getMaxMeasurementEventDate()
{
    return Event::getMaxMeasurementEventDate(*this);
}

QString Baby::getLastMeasures()
{
    return MeasureEvent::getLastMeasures(*this);
}

bool Baby::exportEvents(QString email)
{
    QList<PEvent> events;
    QString exportData;
    PEvent event;
    QString path;
    QMessageAddressList toList;
    QMessage message;
    QMessageAddress address;

    path=QDir::toNativeSeparators(appDataPath+"/babyevents.html");
    QFile file(path);
    if (file.exists())
        file.remove();
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    QDate startDate(1900,1,1);
    QDate endDate(2200,1,1);
    int count=0;

    events=listEvents(startDate, endDate);
    exportData="<html><body><table><tr><th>Date/Time</th><th>Type</th><th>Duration</th><th>Notes</th><th>Height</th><th>Weight</th><th>Cephalic Perimeter</th></tr>\n";
    out << exportData;
    foreach(event,events)
    {
        exportData=QString("<tr><th>%1</th><th>%2</th><th>%3</th><th>%4</th><th>%5</th><th>%6</th><th>%7</th></tr>\n").
                arg(event->getStartDate().toString("yyyy/MM/dd hh:mm")).
                arg(event->getTypeName()).
                arg(event->getDuration()).
                arg(event->getNotes()).
                arg(((double)event->getHeight())/100).
                arg(((double)event->getWeight())/100).
                arg(((double)event->getCephalic())/100);
        out << exportData;
        if (count++ % 10 == 0)
            QApplication::processEvents();
    }
    exportData="</table></body></html>";
    out << exportData;

    file.close();

    address.setAddressee(email);
    address.setType(QMessageAddress::Email);
    toList.append(address);

    message.setTo(toList);
    message.setType(QMessage::Email);
    message.setSubject(getName()+"-BabyFeed Events");
    message.setBody("This email was sent from BabyFeed, the baby agenda app");
    message.appendAttachments(QStringList(path));
    message.setParentAccountId(QMessageAccount::defaultAccount(QMessage::Email));

    if (smsService.getService()->send(message))
    {
        qDebug() << "Message sent";
        return true;
    }
    else
    {
        qDebug() << "Message not sent:error:" << smsService.getService()->error();
        return false;
    }
}
