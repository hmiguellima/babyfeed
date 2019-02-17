#include "eventtypepanel.h"
#include <QSizePolicy>
#include <QVariant>
#include <QMouseEvent>
#include <QMessageBox>
#include "model/event.h"
#include "model/feedingevent.h"
#include "model/medicineevent.h"
#include "model/pottyevent.h"
#include "model/measureevent.h"
#include "model/lfeedingevent.h"
#include "model/rfeedingevent.h"
#include "model/bfeedingevent.h"

#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 86
#define ICON_SIZE 47


void EventTypePanel::initButton(QPushButton* button, QString icon, QString name, char type, QFont& font, PEvent event)
{
    button->sizePolicy().setHorizontalPolicy(QSizePolicy::Fixed);
    button->sizePolicy().setVerticalPolicy(QSizePolicy::Fixed);
    button->setIcon(QIcon(":/icons/icons/"+icon+".png"));
    button->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    button->setFont(font);
    button->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    button->setCheckable(true);
    button->setObjectName(name);
    addWidget(button);
    group->addButton(button);
    mapper->setMapping(button, QString(QChar(type)));
    eventMap[type]=event;
    connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
}


EventTypePanel::~EventTypePanel()
{
}

EventTypePanel::EventTypePanel(QWidget *parent) : KineticScrollArea(parent)
{
    QFont font;
    font.setPointSize(16);

    setStyleSheet("QPushButton {padding-top:0px;padding-bottom:0px}");
    setAutoFillBackground(true);

    layout->setSpacing(0);
    layout->setMargin(0);

    mapper=new QSignalMapper(this);
    group=new QButtonGroup(this);
    group->setExclusive(true);

    lButton=new QPushButton(this);
    bButton=new QPushButton(this);
    rButton=new QPushButton(this);
    mButton=new QPushButton(this);
    pButton=new QPushButton(this);
    wButton=new QPushButton(this);

    initButton(lButton, FeedingEvent::ICON_LEFT, "lButton", Event::TYPE_LEFT_BREAST, font, PEvent(new LFeedingEvent()));
    initButton(bButton, FeedingEvent::ICON_BOTTLE, "bButton", Event::TYPE_BOTTLE, font, PEvent(new BFeedingEvent()));
    initButton(rButton, FeedingEvent::ICON_RIGHT, "rButton", Event::TYPE_RIGHT_BREAST, font, PEvent(new RFeedingEvent()));
    initButton(pButton, PottyEvent::ICON, "pButton", Event::TYPE_POTTY, font, PEvent(new PottyEvent()));
    initButton(mButton, MedicineEvent::ICON, "mButton", Event::TYPE_MEDICINE, font, PEvent(new MedicineEvent()));
    initButton(wButton, MeasureEvent::ICON, "wButton", Event::TYPE_MEASURE, font, PEvent(new MeasureEvent()));

    connect(mapper, SIGNAL(mapped(QString)), this, SLOT(updateEventType(QString)));
    connect(this, SIGNAL(eventSelected(char)), this, SLOT(scrollToSelectedEventType(char)), Qt::QueuedConnection);
    type='L';
}

void EventTypePanel::updateEventType(QString type)
{
    char t;

    t=type.toAscii().at(0);
    this->type=t;

    emit eventSelected(t);
}

void EventTypePanel::setType(char type)
{
    QPushButton *button;

    this->type=type;
    button=qobject_cast<QPushButton*>(mapper->mapping(QString(QChar(type))));
    button->setChecked(true);

    emit eventSelected(type);
}

char EventTypePanel::getType()
{
    return type;
}

void EventTypePanel::scrollToSelectedEventType(char type)
{
    switch (type)
    {
    case Event::TYPE_LEFT_BREAST:
        ensureWidgetVisible(lButton);
        break;
    case Event::TYPE_BOTTLE:
        ensureWidgetVisible(bButton);
        break;
    case Event::TYPE_RIGHT_BREAST:
        ensureWidgetVisible(rButton);
        break;
    case Event::TYPE_POTTY:
        ensureWidgetVisible(pButton);
        break;
    case Event::TYPE_MEDICINE:
        ensureWidgetVisible(mButton);
        break;
    case Event::TYPE_MEASURE:
        ensureWidgetVisible(wButton);
        break;
    }
}

void EventTypePanel::setEnabled(bool enabled)
{
    if (enabled)
    {
        lButton->setEnabled(true);
        bButton->setEnabled(true);
        rButton->setEnabled(true);
        mButton->setEnabled(true);
        pButton->setEnabled(true);
        wButton->setEnabled(true);
    }
    else
    {
        lButton->setEnabled(false);
        bButton->setEnabled(false);
        rButton->setEnabled(false);
        mButton->setEnabled(false);
        pButton->setEnabled(false);
        wButton->setEnabled(false);
        switch(type)
        {
        case Event::TYPE_LEFT_BREAST:
            lButton->setEnabled(true);
            break;
        case Event::TYPE_BOTTLE:
            bButton->setEnabled(true);
            break;
        case Event::TYPE_RIGHT_BREAST:
            rButton->setEnabled(true);
            break;
        case Event::TYPE_MEDICINE:
            mButton->setEnabled(true);
            break;
        case Event::TYPE_POTTY:
            pButton->setEnabled(true);
            break;
        case Event::TYPE_MEASURE:
            wButton->setEnabled(true);
            break;
        }
    }
}

PEvent EventTypePanel::getEvent()
{
    return eventMap[type];
}

void EventTypePanel::resetEventsData()
{
    char t;

    eventMap[t=Event::TYPE_LEFT_BREAST]=PEvent(new LFeedingEvent());
    eventMap[t=Event::TYPE_RIGHT_BREAST]=PEvent(new RFeedingEvent());
    eventMap[t=Event::TYPE_BOTTLE]=PEvent(new BFeedingEvent());
    eventMap[t=Event::TYPE_MEDICINE]=PEvent(new MedicineEvent());
    eventMap[t=Event::TYPE_POTTY]=PEvent(new PottyEvent());
    eventMap[t=Event::TYPE_MEASURE]=PEvent(new MeasureEvent());
}
