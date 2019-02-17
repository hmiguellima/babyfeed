#include "eventmodel.h"
#include "emptyevent.h"
#include <QIcon>

int EventModel::rowCount(const QModelIndex &parent) const
{
    return events.size();
}

QVariant EventModel::headerData(int section, Qt::Orientation orientation,
                    int role) const
{
    return QVariant();
}

QVariant EventModel::data(const QModelIndex& index, int role) const
{
    Event *event;
    QString checkedSufix;

    if (!index.isValid())
        return QVariant();

    if (index.row() >= events.size())
        return QVariant();

    event=events[index.row()].data();

    switch (role)
    {
    case IconRole:
        if (!event->isEmpty())
        {
            if (event->isChecked())
                checkedSufix="_checked.png";
            else
                checkedSufix=".png";

            return QString::fromUtf8(":/icons/icons/")+event->getIcon()+checkedSufix;
        }
        return QVariant();
    case DescRole:
        return QVariant(event->getShortDesc());
    case CheckedRole:
        return QVariant(event->isChecked());
    case EmptyRole:
        return QVariant(event->isEmpty());
    default:
        return QVariant();
    }
}

void EventModel::setEvents(QList<PEvent> &events)
{
    this->events=events;
    reset();
    emit eventsChanged();
}

void EventModel::addEvent(PEvent &event)
{
    if ( (events.size()==1) && (events[0].data()->isEmpty()) )
    {
        events.removeFirst();
        reset();
    }

    events.insert(0, event);
    reset();
    emit eventsChanged();
}

void EventModel::removeEvent(int row)
{
    events.removeAt(row);
    if (events.size()==0)
        events.append(PEvent(new EmptyEvent()));

    reset();
    emit eventsChanged();
}

PEvent EventModel::getEvent(int index)
{
    return events[index];
}

QList<PEvent> EventModel::getEvents()
{
    return events;
}

EventModel::EventModel(QObject *parent) : QAbstractListModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[IconRole] = "icon";
    roles[DescRole] = "desc";
    roles[CheckedRole] = "checked";
    roles[EmptyRole] = "empty";
    setRoleNames(roles);
    events.append(PEvent(new EmptyEvent()));
}
