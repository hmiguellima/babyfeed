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
    case Qt::DecorationRole:
        if (!event->isEmpty())
        {
            if (event->isChecked())
                checkedSufix="_checked.png";
            else
                checkedSufix=".png";

            switch (event->getType())
            {
            case 'L':
                return QIcon(QString::fromUtf8(":/icons/icons/breastfeeding-left")+checkedSufix);
            case 'B':
                return QIcon(QString::fromUtf8(":/icons/icons/baby_bottle")+checkedSufix);
            case 'R':
                return QIcon(QString::fromUtf8(":/icons/icons/breastfeeding-right")+checkedSufix);
            case 'M':
                return QIcon(QString::fromUtf8(":/icons/icons/Pills")+checkedSufix);
            }

        }
        return QVariant();
    case Qt::DisplayRole:
        return QVariant(event->getShortDesc());
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

    //beginInsertRows(QModelIndex(), 1, 1);
    events.insert(0, event);
    reset();
    //endInsertColumns();
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
