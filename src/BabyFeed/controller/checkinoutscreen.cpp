#include <QString>
#include "checkinoutscreen.h"
#include "mainwindow.h"
#include "model/eventmodel.h"
#include "model/eventbus.h"
#include "model/feedingevent.h"
#include <QApplication>

CheckInOutScreen::CheckInOutScreen(MainWindow* window) :
    Screen(window)
{
    contactsModel=new ContactsModel(this);
    view=new CheckInOutView(window, this);
    setView(view);

    timer = new QTimer(this);
    elapsedSecs=0;
    type=Event::TYPE_LEFT_BREAST;

    connect(timer, SIGNAL(timeout()), this, SLOT(displayTime()));
    connect(EventBus::getInstance(), SIGNAL(showCheckInOutScreen(Baby&)), this, SLOT(onShowCheckInOutScreen(Baby&)));
    connect(view, SIGNAL(eventCanceled()), window, SLOT(showMainScreen()));
    connect(view, SIGNAL(leftFeedClicked()), this, SLOT(leftClicked()));
    connect(view, SIGNAL(bottleClicked()), this, SLOT(bottleClicked()));
    connect(view, SIGNAL(rightFeedClicked()), this, SLOT(rightClicked()));
    connect(view, SIGNAL(endEvents()), this, SLOT(notifyEvent()));
    connect(view, SIGNAL(startStopClicked()), this, SLOT(handleStartStop()));
}

CheckInOutScreen::~CheckInOutScreen()
{
}

void CheckInOutScreen::typeButtonClicked(int type)
{
    switch (type)
    {
        case LEFT:
            this->type=Event::TYPE_LEFT_BREAST;
            break;

        case BOTTLE:
            this->type=Event::TYPE_BOTTLE;
            break;

        case RIGHT:
            this->type=Event::TYPE_RIGHT_BREAST;
            break;
    }
}

void CheckInOutScreen::initTime()
{
    view->setParcialTimerText("00:00");
}

void CheckInOutScreen::viewReadyHandler()
{
    setTitle(QString(tr("%0's Feeding Timer")).arg(baby.getName()));
    initTime();
    totalElapsedSecs=0;
}

void CheckInOutScreen::onShowCheckInOutScreen(Baby &baby)
{
    this->baby=baby;
    show();
}


void CheckInOutScreen::displayTime()
{
    QTime lastTime;
    int min;
    int secs;

    lastTime=QTime::currentTime();

    elapsedSecs=startTime.secsTo(lastTime);
    min=elapsedSecs / 60;
    secs=elapsedSecs % 60;
    view->setParcialTimerText(QTime(0, min, secs, 0).toString("mm:ss"));

    min=(totalElapsedSecs+elapsedSecs) / 60;
    secs=(totalElapsedSecs+elapsedSecs) % 60;
    view->setTotalTimerText(QTime(0, min, secs, 0).toString("mm:ss"));
}


void CheckInOutScreen::resetTime()
{
    elapsedSecs=0;
}

void CheckInOutScreen::startTimer()
{
    event=PEvent(new FeedingEvent());

    startTime=QTime::currentTime();

    resetTime();
    timer->start(1000);
    startDateTime=QDateTime::currentDateTime();
}

void CheckInOutScreen::addAlarm(PEvent &event)
{
    QDateTime alarmTime;

    alarmTime=QDateTime::currentDateTime().addSecs(baby.getTimeBetweenFeeds()*60);
    Event::setTimerAlarm(alarmTime, event->getAlarmDesc());
}

void CheckInOutScreen::notifyEvent()
{
    if (baby.isFeedAlarmActive())
        addAlarm(event);

    if (baby.notifyEvent(event, contactsModel))
        getWindow()->showMessageBox(QApplication::tr("BabyFeed"), QApplication::tr("Notifications sent sucessfully"));

    EventBus::getInstance()->fireEventAdded(event);
}

void CheckInOutScreen::stopTimer()
{
    timer->stop();

    event->setDuration(elapsedSecs/60);
    event->setStartDate(startDateTime);
    event->setType(type);
    event->setBabyId(baby.getId());
    event->setChecked(true);

    totalElapsedSecs+=elapsedSecs;
    elapsedSecs=0;

    event->persist();

    initTime();
}

void CheckInOutScreen::leftClicked()
{
    typeButtonClicked(LEFT);
}

void CheckInOutScreen::bottleClicked()
{
    typeButtonClicked(BOTTLE);
}

void CheckInOutScreen::rightClicked()
{
    typeButtonClicked(RIGHT);
}

void CheckInOutScreen::handleStartStop()
{
    if (timer->isActive())
        stopTimer();
    else
        startTimer();
}
