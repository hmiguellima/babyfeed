#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include "event.h"
#include <QAbstractListModel>
#include <QList>
#include <QSharedPointer>
#include <QObject>

class EventModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum RecordRoles {
        IconRole = Qt::UserRole + 1,
        DescRole,
        CheckedRole,
        EmptyRole
    };

    EventModel(QObject* parent);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    void setEvents(QList<PEvent> &events);
    QList<PEvent> getEvents();
    void addEvent(PEvent &event);
    PEvent getEvent(int index);

signals:
    void eventsChanged();

public slots:
    void removeEvent(int row);

private:
    QList<PEvent> events;

};

#endif // EVENTMODEL_H
