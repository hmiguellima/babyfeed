#include <QString>
#include "checkinoutscreen.h"
#include "../BabyFeedApp.hpp"
#include "model/eventmodel.h"
#include "model/eventbus.h"
#include "model/feedingevent.h"
#include <QSettings>

CheckInOutScreen::CheckInOutScreen(BabyFeedApp* window) :
    Screen(window)
{
    view=new CheckInOutView(window, this);
    setView(view);

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(displayTime()));
    connect(EventBus::getInstance(), SIGNAL(showCheckInOutScreen(Baby&)), this, SLOT(onShowCheckInOutScreen(Baby&)));
    connect(view, SIGNAL(startClicked()), this, SLOT(handleStart()));
    connect(view, SIGNAL(stopClicked()), this, SLOT(handleStop()));
    connect(this, SIGNAL(screenInactive()), this, SLOT(handleInactive()));
}

CheckInOutScreen::~CheckInOutScreen()
{
}

void CheckInOutScreen::initTime()
{
	QSettings settings;

	if (settings.contains(QString("timerStart_%1").arg(baby.getId()))) {
		startDateTime=settings.value(QString("timerStart_%1").arg(baby.getId())).toDateTime();
		view->setEventTypeIndex(settings.value(QString("timerType_%1").arg(baby.getId())).toInt());
		view->setRunning(true);
		timer->start();
	}

    view->setTimerText("00:00");
}

void CheckInOutScreen::viewReadyHandler()
{
    setTitle(QString(tr("%0's Feeding Timer")).arg(baby.getName()));
    initTime();
}

void CheckInOutScreen::onShowCheckInOutScreen(Baby &baby)
{
    this->baby=baby;
    show();
}


void CheckInOutScreen::displayTime()
{
    QDateTime lastTime;
    int min;
    int secs;
    int elapsedSecs;

    lastTime=QDateTime::currentDateTime();

    elapsedSecs=startDateTime.secsTo(lastTime);
    min=elapsedSecs / 60;
    secs=elapsedSecs % 60;
    view->setTimerText(QTime(0, min, secs, 0).toString("mm:ss"));
}

void CheckInOutScreen::handleStart()
{
	QSettings settings;

    startDateTime=QDateTime::currentDateTime();
    timer->start(1000);
    view->setRunning(true);

	settings.setValue(QString("timerStart_%1").arg(baby.getId()), startDateTime);
	settings.setValue(QString("timerType_%1").arg(baby.getId()), view->getEventTypeIndex());
}

void CheckInOutScreen::addAlarm(PEvent &event)
{
    QDateTime alarmTime;

    alarmTime=QDateTime::currentDateTime().addSecs(baby.getTimeBetweenFeeds()*60);
    BabyEvent::setTimerAlarm(alarmTime, event->getAlarmDesc());
}

void CheckInOutScreen::handleStop()
{
	QSettings settings;
	QDateTime lastTime;
    int elapsedSecs;
    int eventTypeIndex;
    char eventType='L';
    PEvent event;

    event=PEvent(new FeedingEvent());

	settings.remove(QString("timerStart_%1").arg(baby.getId()));
	settings.remove(QString("timerType_%1").arg(baby.getId()));

    timer->stop();
    view->setRunning(false);
    lastTime=QDateTime::currentDateTime();
    elapsedSecs=startDateTime.secsTo(lastTime);
    eventTypeIndex=view->getEventTypeIndex();

    switch (eventTypeIndex) {
    case 0:
    	eventType='L';
    	break;
    case 1:
    	eventType='B';
    	break;
    case 2:
    	eventType='R';
    	break;
    }

    event->setDuration(elapsedSecs/60);
    event->setStartDate(startDateTime);
    event->setType(eventType);
    event->setBabyId(baby.getId());
    event->setChecked(true);

    event->persist();

    if (baby.isFeedAlarmActive())
        addAlarm(event);

    EventBus::getInstance()->fireEventAdded(event);
}

void CheckInOutScreen::handleInactive() {
	timer->stop();
}


