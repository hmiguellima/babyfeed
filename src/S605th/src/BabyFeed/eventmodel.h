#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include "event.h"
#include <QAbstractListModel>
#include <QList>
#include <QSharedPointer>

class EventModel : public QAbstractListModel
{
    Q_OBJECT

private:
    QList<PEvent> events;

signals:
    void eventsChanged();

public:
    EventModel()
        : QAbstractListModel(0) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    void setEvents(QList<PEvent> &events);
    QList<PEvent> getEvents();
    void addEvent(PEvent &event);
    PEvent getEvent(int index);

public slots:
    void removeEvent(int row);
};

#endif // EVENTMODEL_H
