#include "notification.h"

NotificationData::NotificationData() : QSharedData()
{
    id=-1;
}

NotificationData::~NotificationData()
{
}

NotificationData::NotificationData(const NotificationData &other) : QSharedData(other)
{
    id=other.id;
    type=other.type;
    contact=other.contact;
}

Notification::Notification()
{
    data=new NotificationData();
}

Notification::Notification(int id)
{
    data=new NotificationData();
    data->id=id;
}

int Notification::getId()
{
    return data->id;
}

void Notification::setId(int id)
{
    data->id=id;
}

char Notification::getType()
{
    return data->type;
}

void Notification::setType(char type)
{
    data->type=type;
}

QString Notification::getContact()
{
    return data->contact;
}

void Notification::setContact(QString contact)
{
    data->contact=contact;
}

const bool Notification::operator==(const Notification &other)
{
    return (data->id==other.data->id);
}
