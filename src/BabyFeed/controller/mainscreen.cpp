#include "mainscreen.h"
#include "mainwindow.h"
#include <QSharedPointer>
#include "model/nobaby.h"
#include <QList>
#include "model/eventbus.h"
#include <QSharedPointer>
#include "model/emptyevent.h"
#include <QApplication>
#include <QDate>
#include "mainwindow.h"
#include <QLocale>

#define MAX_BABIES 10

MainScreen::MainScreen(MainWindow* window) :
    Screen(window)
{
    contactsModel=new ContactsModel(this);
    view=new MainView(window, this);
    setView(view);
    date=QDate::currentDate();
    currentBabyIndex=0;

    connect(EventBus::getInstance(), SIGNAL(eventAdded(PEvent&)), this, SLOT(updateEventModelAndShow(PEvent&)));
    connect(EventBus::getInstance(), SIGNAL(eventUpdated(PEvent&)), this, SLOT(updateEventModelAndShow(PEvent&)));
    connect(EventBus::getInstance(), SIGNAL(babySelected(Baby&)), this, SLOT(babySelected(Baby&)));
    connect(EventBus::getInstance(), SIGNAL(babyAdded(Baby&)), this, SLOT(babyAdded(Baby&)));
    connect(EventBus::getInstance(), SIGNAL(babyUpdated(Baby&)), this, SLOT(babyUpdated(Baby&)));
    connect(EventBus::getInstance(), SIGNAL(babyDeleted(Baby&)), this, SLOT(babyDeleted(Baby&)));
    connect(EventBus::getInstance(), SIGNAL(dataReset()), this, SLOT(handleDataReset()));

    connect(view, SIGNAL(babyChanged(int)), this, SLOT(handleBabyPageChange(int)));
    connect(view, SIGNAL(prevDayBtnClicked()), this, SLOT(showPrevDay()));
    connect(view, SIGNAL(nextDayBtnClicked()), this, SLOT(showNextDay()));
    connect(view, SIGNAL(dateSelected(QDate)), this, SLOT(handleDateChanged(QDate)));
    connect(view, SIGNAL(uncheckEventClicked(int)), this, SLOT(handleUncheckEvent(int)));
    connect(view, SIGNAL(checkEventClicked(int)), this, SLOT(handleCheckEvent(int)));
    connect(view, SIGNAL(editEventClicked(int)), this, SLOT(handleEditEvent(int)));
    connect(view, SIGNAL(timerBtnClicked()), this, SLOT(showCheckInOutScreen()));
    connect(view, SIGNAL(eventBtnClicked()), this, SLOT(showManualEventScreen()));
    connect(view, SIGNAL(reportBtnClicked()), this, SLOT(showReportScreen()));
    connect(view, SIGNAL(deleteEventClicked(int)), this, SLOT(handleDeleteEvent(int)));
    connect(view, SIGNAL(editBabyClicked(int)), this, SLOT(handleEditBaby(int)));
    connect(view, SIGNAL(deleteBabyClicked(int)), this, SLOT(handleDeleteBaby(int)));
    connect(view, SIGNAL(newBabyClicked()), this, SLOT(handleNewBaby()));
}

void MainScreen::toogleButtons(bool enable)
{
}

MainScreen::~MainScreen()
{
}

void MainScreen::buildBabyListView()
{    
    QList<PEvent> events;
    Baby baby;

    currentBabyIndex=0;
    events.append(PEvent(new EmptyEvent()));
    babyList=Baby::list();
    view->setBabyList(&babyList);
    foreach(baby,babyList)
    {
        if (baby.isSelected())
            break;
        currentBabyIndex++;
    }

    if (currentBabyIndex==babyList.size())
    {
        currentBabyIndex=0;
        if (babyList.size()>0)
            babyList[currentBabyIndex].persistSelected(true);
    }

    emit babyListBuilt();
}

void MainScreen::showEventInfo(PEvent &event)
{
    EventBus::getInstance()->fireShowEventInfo(event);
}


void MainScreen::updateWindowTitle()
{
    if (currentBabyIndex<babyList.count())
    {
        view->setTitle(babyList[currentBabyIndex].getName()+tr("'s History"));
    }
    else
        view->setTitle(tr("BabyFeed - History"));
}

void MainScreen::updateEventModelAndShow(PEvent &event)
{
    Baby baby;

    baby=babyList[currentBabyIndex];
    eventsList=baby.listEvents(date, date);

    view->setEventsList(&eventsList);
    show();
}

void MainScreen::clearBabySelection()
{
    /*
    if (selectedBabyIcon!=0)
    {
        selectedBabyIcon->setChecked(false);
        selectedBabyIcon->getBaby().persistSelected(false);
        selectedBabyIcon=0;
    }
    */
}

void MainScreen::babySelected(Baby &baby)
{
    eventsList=baby.listEvents(date, date);
    clearBabySelection();
    qApp->processEvents();
    baby.persistSelected(true);
    view->setEventsList(&eventsList);
    updateWindowTitle();
}

void MainScreen::babyAdded(Baby &baby)
{
    clearBabySelection();
    buildBabyListView();
    show();
}

void MainScreen::babyUpdated(Baby &baby)
{
    buildBabyListView();
    show();
}

void MainScreen::babyDeleted(Baby &baby)
{
    buildBabyListView();
    updateWindowTitle();
    handleEventsChanged();
}

void MainScreen::showCheckInOutScreen()
{
    if (currentBabyIndex<babyList.size())
        EventBus::getInstance()->fireShowCheckInOutScreen(babyList[currentBabyIndex]);
}

void MainScreen::showManualEventScreen()
{
    if (currentBabyIndex<babyList.size())
        EventBus::getInstance()->fireShowManualEventScreen(babyList[currentBabyIndex]);
}

void MainScreen::updateCurrentDateLabel()
{
    view->setEventsDate(QLocale().toString(date, tr("ddd, MMM/dd/yyyy")));
}

void MainScreen::showNextDay()
{
    if (currentBabyIndex==babyList.size())
        return;

    date=date.addDays(1);
    updateCurrentDateLabel();

    eventsList=babyList[currentBabyIndex].listEvents(date, date);
    view->setEventsList(&eventsList);
}

void MainScreen::showPrevDay()
{
    if (currentBabyIndex==babyList.size())
        return;

    date=date.addDays(-1);
    updateCurrentDateLabel();

    eventsList=babyList[currentBabyIndex].listEvents(date, date);
    view->setEventsList(&eventsList);
}

void MainScreen::removeEventRow(int row)
{
    PEvent event;

    event=eventsList[row];

    event.data()->remove();
    handleEventsChanged();
}

void MainScreen::showReportScreen()
{
    if (currentBabyIndex<babyList.size())
        EventBus::getInstance()->fireShowReportScreen(babyList[currentBabyIndex]);
}

void MainScreen::scrollToSelectedBaby()
{
//    if (selectedBabyIcon!=0)
//        scroller->ensureWidgetVisible(selectedBabyIcon);
}

void MainScreen::handleDataReset()
{
    buildBabyListView();
    updateWindowTitle();
}

void MainScreen::handleBabyPageChange(int index)
{
    Baby baby;

    if (index==currentBabyIndex)
        return;

    if (currentBabyIndex<babyList.size())
        babyList[currentBabyIndex].persistSelected(false);

    currentBabyIndex=index;

    if (currentBabyIndex<babyList.size())
    {
        baby=babyList[currentBabyIndex];
        baby.persistSelected(true);
        eventsList=baby.listEvents(date, date);
    }
    else
    {
        eventsList= QList<PEvent >();
        eventsList.append(PEvent(new EmptyEvent()));
    }

    view->setEventsList(&eventsList);

    updateWindowTitle();
}

void MainScreen::handleDateChanged(QDate date)
{
    this->date=date;
    updateCurrentDateLabel();
    if (currentBabyIndex<babyList.size())
    {
        eventsList=babyList[currentBabyIndex].listEvents(date, date);
        view->setEventsList(&eventsList);
    }
}

void MainScreen::handleUncheckEvent(int index)
{
    PEvent event;

    event=eventsList[index];

    event->setChecked(!event->isChecked());
    event->persist();
    handleEventsChanged();
}

void MainScreen::handleCheckEvent(int index)
{
    PEvent event;

    event=eventsList[index];

    // se o evento ocurreu nos ultimos MAX_NOTIFICATION_LAG_SECS envia notificações
    if ( (event->getStartDate()<=QDateTime::currentDateTime()) &&
         (event->getStartDate()>=QDateTime::currentDateTime().addSecs(-MAX_NOTIFICATION_LAG_SECS)) )
    {
        if (babyList[currentBabyIndex].notifyEvent(event, contactsModel))
            getWindow()->showMessageBox(tr("BabyFeed"), tr("Notifications sent sucessfully"));
    }
    else
        getWindow()->showMessageBox(tr("BabyFeed"), QString(tr("Notifications only sent when they occurred in the last %0 minutes")).arg(MAX_NOTIFICATION_LAG_SECS/60));

    event->setChecked(!event->isChecked());
    event->persist();
    handleEventsChanged();
}

void MainScreen::handleEditEvent(int index)
{
    PEvent event;

    event=eventsList[index];
    showEventInfo(event);
}

void MainScreen::handleDeleteEvent(int index)
{
    removeEventRow(index);
}


void MainScreen::viewReadyHandler()
{
    buildBabyListView();
    updateWindowTitle();
    updateCurrentDateLabel();
    view->setCurrentBabyIndex(currentBabyIndex);
    handleEventsChanged();
}

void MainScreen::handleEditBaby(int index)
{
    Baby baby;

    baby=babyList[index];
    EventBus::getInstance()->fireShowBabyScreen(baby);
}

void MainScreen::handleDeleteBaby(int index)
{
    Baby baby;

    baby=babyList[index];
    baby.remove();
    EventBus::getInstance()->fireBabyDeleted(baby);
}

void MainScreen::handleNewBaby()
{
    EventBus::getInstance()->fireShowBabyScreen(noBaby);
}

void MainScreen::handleEventsChanged()
{
    if (currentBabyIndex<babyList.size()) {
        eventsList=babyList[currentBabyIndex].listEvents(date, date);
        view->setEventsList(&eventsList);
        view->refreshBaby(currentBabyIndex);
    }
    else
    {
        eventsList= QList<PEvent >();
        eventsList.append(PEvent(new EmptyEvent()));
        view->setEventsList(&eventsList);
    }
}

Baby MainScreen::getCurrentBaby()
{
    if (currentBabyIndex<babyList.size())
        return babyList[currentBabyIndex];
    else
        return noBaby;
}
