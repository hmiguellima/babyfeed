#include "manualeventscreen.h"
#include "model/eventbus.h"
#include <QDate>
#include <QDateTime>
#include <QTime>
#include "model/feedingevent.h"
#include "model/lfeedingevent.h"
#include "model/bfeedingevent.h"
#include "model/rfeedingevent.h"
#include "model/medicineevent.h"
#include "model/measureevent.h"
#include <QMap>
#include "model/pottyevent.h"
#include <QSharedPointer>
#include <QVariant>
#include "../BabyFeedApp.hpp"

#define MAX_EVENTS 50

ManualEventScreen::ManualEventScreen(BabyFeedApp *window) :
    Screen(window)
{
    view=new ManualEventView(window, this);
    setView(view);

    connect(EventBus::getInstance(), SIGNAL(showManualEventScreen(Baby&)), this, SLOT(onShowManualEventScreen(Baby&)));
    connect(EventBus::getInstance(), SIGNAL(showEventInfo(PEvent&)), this, SLOT(onShowEventInfo(PEvent&)));
    connect(view, SIGNAL(save()), this, SLOT(save()));
    connect(view, SIGNAL(deleteEvent()), this, SLOT(deleteEvent()));

    edit=false;
}

ManualEventScreen::~ManualEventScreen()
{
}



void ManualEventScreen::viewReadyHandler()
{
    QDate dataAgora=QDate::currentDate();
    QTime horaAgora=QTime::currentTime();

    setTitle(baby.getName()+tr("'s Event"));

    if (!edit) {
        view->setStartDate(dataAgora);
        view->setDuration(0);
        view->setStartTime(horaAgora);
        view->setEndDate(dataAgora);
        view->setInterval(24);
        view->setEventTypeIndex(BabyEvent::LEFT_BREAST);
        view->setStartDateEnabled(true);
        view->setStartTimeEnabled(true);
        view->setEventTypeBtnRowEnabled(true);
    }
    else
    {
        testAlarm();
        view->setStartDate(event->getStartDate().date());
        view->setStartTime(event->getStartDate().time());
        view->setEventTypeIndex(BabyEvent::getTypeIndex(event->getType()));
        view->setRecurrenceVisible(false);
        view->setEventTypeBtnRowEnabled(false);
        view->setDuration(event->getDuration());
        view->setStartDateEnabled(false);
        view->setStartTimeEnabled(false);
        view->setWeight(event->getWeight());
        view->setHeight(event->getHeight());
        view->setCephalic(event->getCephalic());
        if (BabyEvent::getTypeIndex(event->getType())==BabyEvent::MEDICINE)
        {
            MedicineEvent* medEvent=dynamic_cast<MedicineEvent*>(event.data());
            view->setMedicineName(medEvent->getMedicineName());
            view->setMedicineNotes(medEvent->getNotes());
        }
        else
            view->setGeneralNotes(event->getNotes());

    }
}

void ManualEventScreen::onShowManualEventScreen(Baby &baby)
{
    edit=false;

    this->baby=baby;
    show();
}

void ManualEventScreen::cleanNotes()
{
}

void ManualEventScreen::onShowEventInfo(PEvent &event)
{
    this->event=PEvent(event);

    edit=true;
    baby=Baby::getBabyById(event->getBabyId());
    show();
}

void ManualEventScreen::save()
{
    char eventType;
    QDate startDate;
    QDate endDate;
    QTime startTime;
    QDateTime time;
    int repeatMin;
    int duration;
    int recurrenceId=-1;
    bool notified=false;
    int eventCount;
    PEvent tEvent;
    QString notes;
    QString medName;

    if (edit)
    {
        event->setDuration(view->getDuration());
        event->setType(BabyEvent::getTypeFromIndex(view->getEventTypeIndex()));

        switch (event->getType())
        {
        case BabyEvent::TYPE_LEFT_BREAST:
        case BabyEvent::TYPE_BOTTLE:
        case BabyEvent::TYPE_RIGHT_BREAST:
        case BabyEvent::TYPE_POTTY:
            notes=view->getGeneralNotes();
            event->setNotes(notes);
            break;
        case BabyEvent::TYPE_MEDICINE:
        {
            MedicineEvent* medEvent=dynamic_cast<MedicineEvent*>(event.data());
            medName=view->getMedicineName();
            notes=view->getMedicineNotes();
            medEvent->setMedicineName(medName);
            medEvent->setNotes(notes);
            break;
        }
        case BabyEvent::TYPE_MEASURE:
            event->setWeight(view->getWeight());
            event->setHeight(view->getHeight());
            event->setCephalic(view->getCephalic());
            break;
        }

        event->persist();

        EventBus::getInstance()->fireEventUpdated(event);
    }
    else
    {
        startDate=view->getStartDate();
        endDate=view->getEndDate();
        startTime=view->getStartTime();
        repeatMin=view->getInterval()*60;
        time=QDateTime(startDate, startTime);
        duration=view->getDuration();
        eventType=BabyEvent::getTypeFromIndex(view->getEventTypeIndex());

        switch (view->getEventTypeIndex())
        {
        case BabyEvent::LEFT_BREAST:
            event=PEvent(new LFeedingEvent());
            break;
        case BabyEvent::BOTTLE:
            event=PEvent(new BFeedingEvent());
            break;
        case BabyEvent::RIGHT_BREAST:
            event=PEvent(new RFeedingEvent());
            break;
        case BabyEvent::POTTY:
            event=PEvent(new PottyEvent());
            break;
        case BabyEvent::MEDICINE:
            event=PEvent(new MedicineEvent());
            break;
        case BabyEvent::MEASURE:
            event=PEvent(new MeasureEvent());
            break;
        }

        switch (view->getEventTypeIndex())
        {
        case BabyEvent::LEFT_BREAST:
        case BabyEvent::BOTTLE:
        case BabyEvent::RIGHT_BREAST:
        case BabyEvent::POTTY:
            notes=view->getGeneralNotes();
            event->setNotes(notes);
            break;
        case BabyEvent::MEDICINE:
        {
            MedicineEvent* medEvent=dynamic_cast<MedicineEvent*>(event.data());

            medName=view->getMedicineName();
            if (medName.trimmed().length()==0)
            {
                getWindow()->showMessageBox(tr("Invalid event"), QString(tr("Please enter the medicine name")));
                return;
            }
            medEvent->setMedicineName(medName);
            notes=view->getMedicineNotes();
            medEvent->setNotes(notes);
            break;
        }
        case BabyEvent::MEASURE:
            event->setWeight(view->getWeight());
            event->setHeight(view->getHeight());
            event->setCephalic(view->getCephalic());
            break;
        }

        eventCount=time.secsTo(QDateTime(endDate, QTime(23,59,59,59)))/(repeatMin*60);
        if (eventCount > MAX_EVENTS)
        {
            getWindow()->showMessageBox(tr("Invalid event"), QString(tr("The maximum event count for a recurrence is %0 events!")).arg(MAX_EVENTS));
            return;
        }

        if ( (time.date()>endDate) || (startDate > endDate) )
        {
            getWindow()->showMessageBox(tr("Invalid event"), tr("The scheduled end date is inválid!"));
            return;
        }

        if ((repeatMin<24)||(time.date()<endDate))
            recurrenceId=BabyEvent::getNextRecurrenceId();

        getWindow()->showBusyBox();

        while (time.date()<=endDate)
        {
            QApplication::processEvents();

            tEvent = event->clone();

            tEvent->setBabyId(baby.getId());
            tEvent->setStartDate(time);
            tEvent->setDuration(duration);
            tEvent->setType(eventType);
            tEvent->setRecurrenceId(recurrenceId);
            if (time<=QDateTime::currentDateTime())
            {
                tEvent->setChecked(true);
            }
            else
                if (tEvent->getAlarmDesc().length()>0)
                    tEvent->setAlarm(time, time, tEvent->getAlarmDesc());

            tEvent->persist();

            if (repeatMin==0)
                time=time.addDays(1);
            else
                time=time.addSecs(repeatMin*60);
        }

        getWindow()->hideBusyBox();

        if (notified)
            getWindow()->showMessageBox(QApplication::tr("BabyFeed"), QApplication::tr("Notifications sent sucessfully"));
        EventBus::getInstance()->fireEventAdded(event);
    }
}

void ManualEventScreen::deleteEvent() {
	event->remove();
}

void ManualEventScreen::testAlarm()
{
}
