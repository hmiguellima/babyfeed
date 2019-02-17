#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "mainwindow.h"
#include "babyicon.h"
#include <QHBoxLayout>
#include <QWidget>
#include <QSharedPointer>
#include <QSpacerItem>
#include <QScrollArea>
#include <QScrollBar>
#include <QPushButton>
#include "nobaby.h"
#include "kineticscrollarea.h"
#include <QList>
#include "eventbus.h"
#include <QSharedPointer>
#include "emptyevent.h"
#include <QListView>

MainScreen::MainScreen(MainWindow* window) :
    Screen(window),
    ui(new Ui::MainScreen)
{
    ui->setupUi(this);
    kineticScroller1.setWidget(ui->scrollArea);
    kineticScroller2.setWidget(ui->listView);

    eventMenu=new QComboBox(this);
    eventMenu->setVisible(false);

    ui->listView->setVerticalScrollMode(QListView::ScrollPerPixel);
    ui->listView->setIconSize(QSize(32, 32));
    ui->listView->setModel(&model);

    connect(EventBus::getInstance(), SIGNAL(eventAdded(PEvent&)), this, SLOT(updateEventModelAndShow(PEvent&)));
    connect(EventBus::getInstance(), SIGNAL(eventUpdated(PEvent&)), this, SLOT(updateEventModelAndShow(PEvent&)));
    connect(ui->checkInOutButton, SIGNAL(clicked()), this, SLOT(showCheckInOutScreen()));
    connect(ui->manualButton, SIGNAL(clicked()), this, SLOT(showManualEventScreen()));
    connect(ui->statsButton, SIGNAL(clicked()), this, SLOT(showReportScreen()));
    connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(showEventMenu(QModelIndex)));
    connect(EventBus::getInstance(), SIGNAL(babySelected(Baby&)), this, SLOT(babySelected(Baby&)));
    connect(EventBus::getInstance(), SIGNAL(babyAdded(Baby&)), this, SLOT(babyAdded(Baby&)));
    connect(EventBus::getInstance(), SIGNAL(babyUpdated(Baby&)), this, SLOT(babyUpdated(Baby&)));
    connect(EventBus::getInstance(), SIGNAL(babyDeleted(Baby&)), this, SLOT(babyDeleted(Baby&)));
    connect(EventBus::getInstance(), SIGNAL(dataReset()), this, SLOT(buildBabyListView()));
    connect(ui->nextDayButton, SIGNAL(clicked()), this, SLOT(showNextDay()));
    connect(ui->prevDayButton, SIGNAL(clicked()), this, SLOT(showPrevDay()));
    connect(eventMenu, SIGNAL(activated(int)), this, SLOT(handleEventMenuActivated(int)));
    connect(this, SIGNAL(babyListBuilt()), this, SLOT(scrollToSelectedBaby()), Qt::QueuedConnection);

    scroller=new KineticScrollArea(this, KineticScrollArea::HorizontalScrollDir);
    ui->babyLayout->addWidget(scroller);

    date=QDate::currentDate();
    updateCurrentDateLabel();

    buildBabyListView();
}

void MainScreen::toogleButtons(bool enable)
{
    ui->checkInOutButton->setEnabled(enable);
    ui->manualButton->setEnabled(enable);
    ui->statsButton->setEnabled(enable);
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::buildBabyListView()
{    
    BabyIcon *icon;
    NoBaby noBaby;
    Baby iBaby;
    QList<Baby> babyList;
    QList<PEvent> events;

    events.append(QSharedPointer<Event>(new EmptyEvent()));

    babyList=Baby::list();

    selectedBabyIcon=0;
    iconMap.clear();

    scroller->clearWidgets();

    foreach(iBaby, babyList)
    {
        icon=new BabyIcon(iBaby);
        iconMap.insert(iBaby.getId(), icon);
        scroller->addWidget(icon);
        if (icon->isSelected())
            selectedBabyIcon=icon;
    }

    if (selectedBabyIcon!=0)
        events=selectedBabyIcon->getBaby().listEvents(date, date);
    model.setEvents(events);

    icon=new BabyIcon(noBaby);
    scroller->addWidget(icon);

    emit babyListBuilt();
}

void MainScreen::showEventInfo(PEvent &event)
{
    EventBus::getInstance()->fireShowEventInfo(event);
}


void MainScreen::updateWindowTitle()
{
    if (selectedBabyIcon!=0)
        getWindow()->setWindowTitle(selectedBabyIcon->getBaby().getName()+"'s History");
    else
        getWindow()->setWindowTitle(tr("BabyFeed - History"));
}

void MainScreen::showHandler()
{
    updateWindowTitle();
}

void MainScreen::updateEventModelAndShow(PEvent &event)
{
    QList<PEvent> events;

    events=selectedBabyIcon->getBaby().listEvents(date, date);
    model.setEvents(events);
    show();
}

void MainScreen::clearBabySelection()
{
    if (selectedBabyIcon!=0)
    {
        selectedBabyIcon->setSelected(false);
        selectedBabyIcon->getBaby().setSelected(false);
        selectedBabyIcon->getBaby().persist();
        selectedBabyIcon=0;
    }
}

void MainScreen::babySelected(Baby &baby)
{
    QList<PEvent> events=baby.listEvents(date, date);

    clearBabySelection();
    selectedBabyIcon=iconMap[baby.getId()];
    baby.setSelected(true);
    baby.persist();

    model.setEvents(events);
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
    show();
}

void MainScreen::showCheckInOutScreen()
{
    if (selectedBabyIcon!=0)
        EventBus::getInstance()->fireShowCheckInOutScreen(selectedBabyIcon->getBaby());
}

void MainScreen::showManualEventScreen()
{
    if (selectedBabyIcon!=0)
        EventBus::getInstance()->fireShowManualEventScreen(selectedBabyIcon->getBaby());
}

void MainScreen::updateCurrentDateLabel()
{
    ui->currentDateLabel->setText(date.toString("ddd, MMM/dd/yyyy"));
}

void MainScreen::showNextDay()
{
    QList<PEvent> events;

    date=date.addDays(1);
    updateCurrentDateLabel();
    if (selectedBabyIcon!=0)
        events=selectedBabyIcon->getBaby().listEvents(date, date);
    model.setEvents(events);
}

void MainScreen::showPrevDay()
{
    QList<PEvent> events;

    date=date.addDays(-1);
    updateCurrentDateLabel();
    if (selectedBabyIcon!=0)
        events=selectedBabyIcon->getBaby().listEvents(date, date);
    model.setEvents(events);
}

void MainScreen::showEventMenu(QModelIndex index)
{
    int row;
    PEvent event;

    row=index.row();
    event=model.getEvent(row);
    if (!event.data()->isEmpty())
    {
        eventMenu->clear();
        if (event->isChecked())
            eventMenu->addItem(tr("Uncheck"), QVariant(row));
        else
            eventMenu->addItem(tr("Check"), QVariant(row));
        eventMenu->addItem(tr("Edit"), QVariant(row));
        eventMenu->addItem(tr("Delete"), QVariant(row));
        eventMenu->showPopup();
    }
}

void MainScreen::handleEventMenuActivated(int index)
{
    PEvent event;
    int row;

    row=eventMenu->itemData(index).toInt();
    event=model.getEvent(row);

    switch(index)
    {
    case 0:
        if (!event->isChecked())
            selectedBabyIcon->getBaby().notifyEvent(event);
        event->setChecked(!event->isChecked());
        event->persist();
        break;
    case 1: showEventInfo(event);break;
    case 2: removeEventRow(row);break;
    }

}

void MainScreen::removeEventRow(int row)
{
    PEvent event;
    event=model.getEvent(row);
    int ret;

    ret=QMessageBox::warning(this, tr("BabyFeed"), tr("Do you want to remove this event?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret==QMessageBox::Yes)
    {
        event.data()->remove();
        model.removeEvent(row);
    }
}

void MainScreen::showReportScreen()
{
    EventBus::getInstance()->fireShowReportScreen(selectedBabyIcon->getBaby());
}

void MainScreen::scrollToSelectedBaby()
{
    if (selectedBabyIcon!=0)
        scroller->ensureWidgetVisible(selectedBabyIcon);
}
