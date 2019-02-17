#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QSharedData>
#include <QExplicitlySharedDataPointer>
#include <QString>

class NotificationData : public QSharedData
{
public:
    NotificationData();
    NotificationData(const NotificationData &other);
    ~NotificationData();

    int id;
    char type;
    QString contact;
};

class Notification
{
public:
    Notification();
    Notification(int id);

    int getId();
    void setId(int id);
    char getType();
    void setType(char type);
    QString getContact();
    void setContact(QString contact);
    const bool operator==(const Notification &other);
private:
    QExplicitlySharedDataPointer<NotificationData> data;
};

#endif // NOTIFICATION_H
