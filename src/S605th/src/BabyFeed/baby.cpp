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
#ifdef Q_OS_SYMBIAN
    //#include "messaging/xqmessaging.h"
#endif

BabyData::BabyData()
{
    photo=QImage(QString::fromUtf8(":/icons/icons/baby_icon.jpg"));
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
    photo=other.photo;
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

QImage Baby::getPhoto()
{
    return data->photo;
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

void Baby::setPhoto(QImage &photo)
{
    data->photo=photo;
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
    if (Baby::hasPhoto(baby))
    {
        photo.load(Baby::getPhotoFileName(baby));
        baby.setPhoto(photo);
    }
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
    return QString::number(baby.getId())+".jpg";
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

    data->photo.save(getPhotoFileName(*this));
}

void Baby::remove()
{
    QSqlQuery query;

    query.exec("delete from Baby where baby_id="+QString::number(getId()));
    query.exec("delete from Notification where notf_baby_id="+QString::number(getId()));

    QFile::remove(getPhotoFileName(*this));
}

QList<PEvent> Baby::listEvents(QDate &startDate, QDate &endDate)
{
    return Event::list(*this, startDate, endDate);
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

void Baby::notifyEvent(PEvent &event)
{
    Notification notf;
    QString phone;
    QStringList phoneList;

    foreach(notf, data->notifications)
    {
        if (  ( (notf.getType()=='F') && (event->getType()!='M') ) ||
              (notf.getType()==event->getType()) ||
              (notf.getType()=='B') )
        {
            phone=ContactsModel::getContactPhone(notf.getContact());
            phoneList << phone;
        }
    }

    if (phoneList.count()>0)
    {
#ifdef Q_OS_SYMBIAN
            //XQMessage msg(phoneList, event->getNotfDesc());
            //XQMessaging messaging;

            //if (messaging.send(msg))
                QMessageBox::information(0, QApplication::tr("BabyFeed"), QApplication::tr("Notification sent sucessfully"));
            //else
            //    QMessageBox::information(0, QApplication::tr("BabyFeed"), QApplication::tr("Notification failed"));
#else
            QMessageBox::information(0, QApplication::tr("BabyFeed"), QApplication::tr("Notification sent sucessfully"));
#endif
    }
}
