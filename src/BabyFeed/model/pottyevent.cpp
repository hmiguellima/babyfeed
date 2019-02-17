#include "pottyevent.h"
#include <QApplication>
#include <QDateTime>
#include <QString>
#include "baby.h"

const QString PottyEvent::ICON="nappy";

PottyEvent::PottyEvent() : Event()
{
    setType(Event::TYPE_POTTY);
}

QString PottyEvent::getShortDesc()
{
    return QApplication::tr("At: ")+getStartDate().toString("hh:mm");
}

QString PottyEvent::getAlarmDesc()
{
    return "";
}

QString PottyEvent::getNotfDesc()
{
    QString babyName=Baby::getBabyById(getBabyId()).getName();
    return babyName+QApplication::tr("'s diaper event at: ")+getStartDate().toString("hh:mm");
}

QString PottyEvent::getIcon()
{
    return ICON;
}

PEvent PottyEvent::clone()
{
    PEvent event=PEvent(new PottyEvent());
    QString notes;

    notes=getNotes();
    event->setNotes(notes);

    return event;
}

bool PottyEvent::isRecurrentAble()
{
    return false;
}
