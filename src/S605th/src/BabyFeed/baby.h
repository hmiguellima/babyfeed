#ifndef BABY_H
#define BABY_H
#include <QString>
#include <QIcon>
#include <QDateTime>
#include <QSharedData>
#include <QSharedDataPointer>
#include <QSharedPointer>
#include <QList>
#include <QSqlQuery>
#include "event.h"
#include <QDate>
#include "notification.h"
#include <QSet>


enum Gender
{
    Boy,
    Girl,
    NewBaby
};

class BabyData : public QSharedData
{
public:
    BabyData();
    BabyData(const BabyData& other);
    ~BabyData();

    QImage photo;
    QString name;
    QDateTime birthDate;
    Gender gender;
    int id;
    bool selected;
    bool feedAlarmActive;
    int timeBetweenFeeds;
    QList<Notification> oldNotifications;
    QList<Notification> notifications;
};

class Baby
{
public:
    Baby();
    ~Baby();

    int getId();
    virtual QImage getPhoto();
    virtual QString getName();
    QDateTime getBirthDate();
    Gender getGender();
    void setId(int id);
    void setBirthDate(QDateTime date);
    void setName(QString name);
    void setPhoto(QImage &photo);
    void setGender(Gender gender);
    void persist();
    void remove();
    bool isSelected();
    void setSelected(bool selected);
    QList<PEvent> listEvents(QDate &startDate, QDate &endDate);
    void setFeedAlarmActive(bool active);
    bool isFeedAlarmActive();
    void setTimeBetweenFeeds(int time);
    int getTimeBetweenFeeds();
    char getNotificationType(QString contactKey);
    void addNotification(QString contactKey, char type);
    void removeNotification(QString contactKey);
    void updateNotfication(QString contactKey, char type);
    QSet<QString> getNotfContactKeys();
    void notifyEvent(PEvent &event);

    static QList<Baby> list();
    static Baby getSelectedBaby();
    static Baby getBabyById(int id);

protected:
    QSharedDataPointer<BabyData> data;

    void loadNotifications();
    void syncNotifications();

    static QString fields();
    static QString getPhotoFileName(Baby &baby);
    static bool hasPhoto(Baby &baby);
    static Baby getBabyFromQuery(QSqlQuery *query);
};



#endif // BABY_H
