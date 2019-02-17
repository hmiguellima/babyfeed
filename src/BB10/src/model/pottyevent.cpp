#include "pottyevent.h"
#include <QDateTime>
#include <QString>
#include "baby.h"

const QString PottyEvent::ICON="nappy";

PottyEvent::PottyEvent() : BabyEvent()
{
    setType(BabyEvent::TYPE_POTTY);
}

QString PottyEvent::getShortDesc()
{
    return QObject::tr("At: ")+getStartDate().toString("hh:mm");
}

QString PottyEvent::getAlarmDesc()
{
    return "";
}

QString PottyEvent::getNotfDesc()
{
    QString babyName=Baby::getBabyById(getBabyId()).getName();
    return babyName+QObject::tr("'s diaper event at: ")+getStartDate().toString("hh:mm");
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
