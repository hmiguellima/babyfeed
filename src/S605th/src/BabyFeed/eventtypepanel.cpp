#include "eventtypepanel.h"
#include <QSizePolicy>
#include <QVariant>
#include <QMouseEvent>
#include <QMessageBox>

#define BUTTON_WIDTH 118
#define BUTTON_HEIGHT 70

EventTypePanel::EventTypePanel(QWidget *parent) : KineticScrollArea(parent, KineticScrollArea::HorizontalScrollDir)
{
    QFont font;
    font.setPointSize(16);

    layout->setSpacing(0);
    layout->setMargin(0);

    mapper=new QSignalMapper(this);
    group=new QButtonGroup(this);
    group->setExclusive(true);

    lButton=new QPushButton(this);
    bButton=new QPushButton(this);
    rButton=new QPushButton(this);
    mButton=new QPushButton(this);

    lButton->sizePolicy().setHorizontalPolicy(QSizePolicy::Fixed);
    lButton->sizePolicy().setVerticalPolicy(QSizePolicy::Fixed);
    lButton->setIcon(QIcon(":/icons/icons/breastfeeding-left.png"));
    lButton->setIconSize(QSize(38, 38));
    lButton->setFont(font);
    lButton->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    lButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    lButton->setCheckable(true);
    lButton->setObjectName("lButton");
    addWidget(lButton);
    group->addButton(lButton);
    mapper->setMapping(lButton, "L");
    connect(lButton, SIGNAL(clicked()), mapper, SLOT(map()));

    bButton->sizePolicy().setHorizontalPolicy(QSizePolicy::Fixed);
    bButton->sizePolicy().setVerticalPolicy(QSizePolicy::Fixed);
    bButton->setIcon(QIcon(":/icons/icons/baby_bottle.png"));
    bButton->setIconSize(QSize(38, 38));
    bButton->setFont(font);
    bButton->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    bButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    bButton->setCheckable(true);
    bButton->setObjectName("bButton");
    addWidget(bButton);
    group->addButton(bButton);
    mapper->setMapping(bButton, "B");
    connect(bButton, SIGNAL(clicked()), mapper, SLOT(map()));

    rButton->sizePolicy().setHorizontalPolicy(QSizePolicy::Fixed);
    rButton->sizePolicy().setVerticalPolicy(QSizePolicy::Fixed);
    rButton->setIcon(QIcon(":/icons/icons/breastfeeding-right.png"));
    rButton->setIconSize(QSize(38, 38));
    rButton->setFont(font);
    rButton->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    rButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    rButton->setCheckable(true);
    rButton->setObjectName("rButton");
    addWidget(rButton);
    group->addButton(rButton);
    mapper->setMapping(rButton, "R");
    connect(rButton, SIGNAL(clicked()), mapper, SLOT(map()));

    mButton->sizePolicy().setHorizontalPolicy(QSizePolicy::Fixed);
    mButton->sizePolicy().setVerticalPolicy(QSizePolicy::Fixed);
    mButton->setIcon(QIcon(":/icons/icons/Pills.png"));
    mButton->setIconSize(QSize(38, 38));
    mButton->setFont(font);
    mButton->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    mButton->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    mButton->setCheckable(true);
    mButton->setObjectName("mButton");
    addWidget(mButton);
    group->addButton(mButton);
    mapper->setMapping(mButton, "M");
    connect(mButton, SIGNAL(clicked()), mapper, SLOT(map()));

    connect(mapper, SIGNAL(mapped(QString)), this, SLOT(updateEventType(QString)));
    connect(this, SIGNAL(eventSelected(char)), this, SLOT(scrollToSelectedEventType(char)), Qt::QueuedConnection);
    type=0;
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
    case 'L':
        ensureWidgetVisible(lButton);
        break;
    case 'B':
        ensureWidgetVisible(bButton);
        break;
    case 'R':
        ensureWidgetVisible(rButton);
        break;
    case 'M':
        ensureWidgetVisible(mButton);
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
    }
    else
    {
        lButton->setEnabled(false);
        bButton->setEnabled(false);
        rButton->setEnabled(false);
        mButton->setEnabled(false);
        switch(type)
        {
        case 'L':
            lButton->setEnabled(true);
            break;
        case 'B':
            bButton->setEnabled(true);
            break;
        case 'R':
            rButton->setEnabled(true);
            break;
        case 'M':
            mButton->setEnabled(true);
            break;
        }
    }
}
