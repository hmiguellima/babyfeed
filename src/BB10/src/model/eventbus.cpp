#include "eventbus.h"

EventBus *EventBus::instance=new EventBus();

EventBus::EventBus() : QObject()
{
}

EventBus::~EventBus()
{
}


EventBus* EventBus::getInstance() {
    return instance;
}

void EventBus::fireEventAdded(PEvent &event)
{
    emit eventAdded(event);
}

void EventBus::fireEventDeleted(PEvent &event)
{
    emit eventDeleted(event);
}

void EventBus::fireBabyAdded(Baby &baby)
{
    emit babyAdded(baby);
}

void EventBus::fireBabyDeleted(Baby &baby)
{
    emit babyDeleted(baby);
}

void EventBus::fireShowMainScreen()
{
    emit showMainScreen();
}

void EventBus::fireShowBabyScreen(Baby &baby)
{
    emit showBabyScreen(baby);
}

void EventBus::fireShowCheckInOutScreen(Baby &baby)
{
    emit showCheckInOutScreen(baby);
}

void EventBus::fireShowManualEventScreen(Baby &baby)
{
    emit showManualEventScreen(baby);
}

void EventBus::fireShowOptionsScreen()
{
    emit showOptionsScreen();
}

void EventBus::fireShowCameraScreen()
{
    emit showCameraScreen();
}

void EventBus::fireBabyPhotoCaptured(QByteArray data)
{
    emit babyPhotoCaptured(data);
}


void EventBus::fireBabyPhotoAborted()
{
    emit babyPhotoAborted();
}

void EventBus::fireBabySelected(Baby &baby)
{
    emit babySelected(baby);
}

void EventBus::fireBabyUpdated(Baby &baby)
{
    emit babyUpdated(baby);
}

void EventBus::fireDataReset()
{
    emit dataReset();
}


void EventBus::fireShowEventInfo(PEvent &event)
{
    emit showEventInfo(event);
}

void EventBus::fireEventUpdated(PEvent &event)
{
    emit eventUpdated(event);
}

void EventBus::fireShowReportScreen(Baby &baby)
{
    emit showReportScreen(baby);
}

