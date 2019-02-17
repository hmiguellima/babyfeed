#include "eventmodel.h"
#include "emptyevent.h"

using namespace bb::cascades;

EventModel::EventModel(QObject *parent) : QListDataModel()
{
	setParent(parent);
}

void EventModel::setEvents(QList<PEvent>* events)
{
    this->_eventsList=events;
    refresh();
}

void EventModel::refresh() {
    PEvent event;
    QString checkedSufix;

    clear();

    for (int i = 0; i < _eventsList->size(); i++){
        QVariantMap map;

        event=_eventsList->at(i);

        if (!event->isEmpty())
        {
            if (event->isChecked())
                checkedSufix="_checked.png";
            else
                checkedSufix=".png";

            //map.insert("iconUrl", QString::fromUtf8("asset:///images/")+event->getIcon()+checkedSufix);
            map.insert("iconUrl", QString::fromUtf8("asset:///images/")+event->getIcon()+".png");
        }

        map.insert("desc", event->getShortDesc());
        map.insert("checked", event->isChecked());
        map.insert("empty", event->isEmpty());
        map.insert("id", event->getId());

        append(map);
    }
}
