#include <QString>
#include <QSignalMapper>
#include <QMenuBar>
#include <QAction>
#include "checkinoutscreen.h"
#include "ui_checkinoutscreen.h"
#include "mainwindow.h"
#include "eventmodel.h"
#include "eventbus.h"
#include "feedingevent.h"

CheckInOutScreen::CheckInOutScreen(MainWindow* window) :
    Screen(window),
    ui(new Ui::CheckInOutScreen)
{
    QSignalMapper *mapper=new QSignalMapper(this);

    ui->setupUi(this);

    startAction=new QAction(tr("Start"), this);
    startAction->setSoftKeyRole(QAction::PositiveSoftKey);

    stopAction=new QAction(tr("Stop"), this);
    stopAction->setSoftKeyRole(QAction::NegativeSoftKey);

    ui->lButton->setChecked(true);
    ui->bButton->setChecked(false);
    ui->rButton->setChecked(false);

    mapper->setMapping(ui->lButton, LEFT);
    mapper->setMapping(ui->bButton, BOTTLE);
    mapper->setMapping(ui->rButton, RIGHT);

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(displayTime()));
    connect(startAction, SIGNAL(triggered()), this, SLOT(startTimer()));
    connect(stopAction, SIGNAL(triggered()), this, SLOT(stopTimer()));
    connect(ui->lButton, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    connect(ui->bButton, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    connect(ui->rButton, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(typeButtonClicked(int)));

    connect(EventBus::getInstance(), SIGNAL(showCheckInOutScreen(Baby&)), this, SLOT(onShowCheckInOutScreen(Baby&)));

    elapsedSecs=0;
    type='L';
}

CheckInOutScreen::~CheckInOutScreen()
{
    delete ui;
}

void CheckInOutScreen::typeButtonClicked(int type)
{
    switch (type)
    {
        case LEFT:
            this->type='L';
            break;

        case BOTTLE:
            this->type='B';
            break;

        case RIGHT:
            this->type='R';
            break;
    }
}

void CheckInOutScreen::showHandler()
{
    ui->lcdNumber->display("00:00");
    ui->lButton->setEnabled(true);
    ui->bButton->setEnabled(true);
    ui->rButton->setEnabled(true);

    if (!actions().contains(startAction))
        addAction(startAction);

    if (actions().contains(stopAction))
        removeAction(stopAction);

    addAction(getWindow()->getInstance()->getBackAction());
}

void CheckInOutScreen::onShowCheckInOutScreen(Baby &baby)
{
    this->baby=baby;
    getWindow()->setWindowTitle(baby.getName()+"'s Feeding Timer");
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

    ui->lcdNumber->display(QTime(0, min, secs, 0).toString("mm:ss"));
}

void CheckInOutScreen::startTimer()
{
    startTime=QTime::currentTime();
    ui->lcdNumber->display("00:00");
    removeAction(startAction);
    removeAction(getWindow()->getBackAction());
    addAction(stopAction);
    ui->lButton->setEnabled(false);
    ui->bButton->setEnabled(false);
    ui->rButton->setEnabled(false);
    timer->start(1000);
    startDateTime=QDateTime::currentDateTime();
    setFocus();
}

void CheckInOutScreen::addAlarm(PEvent &event)
{
    event->setAlarm(QDateTime::currentDateTime().addSecs(baby.getTimeBetweenFeeds()*60),
                   event->getAlarmDesc());
}

void CheckInOutScreen::stopTimer()
{
    PEvent event=PEvent(new FeedingEvent());

    if (!timer->isActive())
    {
        EventBus::getInstance()->fireShowMainScreen();
        return;
    }

    timer->stop();

    event->setDuration(elapsedSecs/60);
    event->setStartDate(startDateTime);
    event->setType(type);
    event->setBabyId(baby.getId());
    event->setChecked(true);

    elapsedSecs=0;

    event->persist();

    if (baby.isFeedAlarmActive())
        addAlarm(event);

    EventBus::getInstance()->fireEventAdded(event);
}
