#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include <bb/cascades/databinding/qlistdatamodel.h>
#include <QList>
#include <QVariantMap>
#include "event.h"
#include <QSharedPointer>

class EventModel : public bb::cascades::QListDataModel<QVariantMap>
{
public:
    EventModel(QObject* parent);
    void setEvents(QList<PEvent>* events);
    void refresh();

private:
    QList<PEvent>* _eventsList;
};

#endif // EVENTMODEL_H
