#ifndef BABY_H
#define BABY_H
#include <QString>
#include <QDateTime>
#include <QSharedData>
#include <QExplicitlySharedDataPointer>
#include <QSharedPointer>
#include <QList>
#include <QtSql/QSqlQuery>
#include "event.h"
#include <QDate>
#include "notification.h"
#include <QSet>
#include <QMetaType>

enum Gender
{
    Boy,
    Girl,
    NewBaby
};

class ContactsModel;

class BabyData : public QSharedData
{
public:
    BabyData();
    BabyData(const BabyData& other);
    ~BabyData();

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

class Baby : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString name READ getName)
	Q_PROPERTY(QString photo READ getPhoto)
	Q_PROPERTY(QString age READ getAge)
	Q_PROPERTY(QString measures READ getLastMeasures)

public:
	Baby();
	Baby(QString name);
	Baby(const Baby& other);
    virtual ~Baby();

    Baby& operator=(const Baby& other);
    int getId();
    virtual QString getName();
    virtual QString getAge();
    virtual QString getPhoto();
    QDateTime getBirthDate();
    Gender getGender();
    void setId(int id);
    void setBirthDate(QDateTime date);
    void setName(QString name);
    void setGender(Gender gender);
    void persist();
    void remove();
    bool isSelected();
    void setSelected(bool selected);
    void persistSelected(bool selected);
    QList<PEvent> listEvents(QDate &startDate, QDate &endDate);
    QList<PEvent> listFeedEvents(QDate &startDate, QDate &endDate);
    QList<PEvent> listMeasureEvents(QDate &startDate, QDate &endDate);
    QList<PEvent> getLastMeasureEvent();
    void setFeedAlarmActive(bool active);
    bool isFeedAlarmActive();
    void setTimeBetweenFeeds(int time);
    int getTimeBetweenFeeds();
    char getNotificationType(QString contactKey);
    void addNotification(QString contactKey, char type);
    void removeNotification(QString contactKey);
    void updateNotfication(QString contactKey, char type);
    QSet<QString> getNotfContactKeys();
    bool notifyEvent(PEvent &event, ContactsModel* contactsModel);
    QDate getMinFeedEventDate();
    QDate getMaxFeedEventDate();
    QDate getMinMeasurementEventDate();
    QDate getMaxMeasurementEventDate();
    virtual QString getLastMeasures();
    bool exportEvents(QString email);

    static QList<Baby> list();
    static Baby getSelectedBaby();
    static Baby getBabyById(int id);
    static bool hasPhoto(Baby &baby);
    static QString getPhotoFileName(Baby &baby);
    static QString getPhotoUri(Baby &baby);

signals:
    void birthdayChanged();

protected:
    QExplicitlySharedDataPointer<BabyData> data;

    void loadNotifications();
    void syncNotifications();
    QList<PEvent> listEvents(QDate &startDate, QDate &endDate, QString filter);

    static QString fields();
    static Baby getBabyFromQuery(QSqlQuery *query);
};

Q_DECLARE_METATYPE(Baby)

#endif // BABY_H
