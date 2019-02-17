#include "medicineevent.h"
#include <QStringList>
#include <QString>
#include "baby.h"

const QString MedicineEvent::ICON="Pills";

MedicineEvent::MedicineEvent() : BabyEvent()
{
    QString notes="|";
    BabyEvent::setNotes(notes);
    setType(BabyEvent::TYPE_MEDICINE);
}

QString MedicineEvent::getMedicineName()
{
    return BabyEvent::getNotes().split("|").at(0);
}

void MedicineEvent::setMedicineName(QString &medicineName)
{
    QString notes=medicineName+"|"+getNotes();
    BabyEvent::setNotes(notes);
}

QString MedicineEvent::getNotes()
{
    return BabyEvent::getNotes().split("|").at(1);
}

void MedicineEvent::setNotes(QString &notes)
{
    QString newNotes=getMedicineName()+"|"+notes;
    BabyEvent::setNotes(newNotes);
}


QString MedicineEvent::getShortDesc()
{
    QString eventData;

    eventData=getMedicineName()+QObject::tr(" at: ")+getStartDate().toString("hh:mm");

    return eventData;
}

QString MedicineEvent::getAlarmDesc()
{
    QString babyName=Baby::getBabyById(getBabyId()).getName();
    return QObject::tr("It's time to give ")+getMedicineName()+QObject::tr(" to ")+babyName;
}

QString MedicineEvent::getNotfDesc()
{
    QString babyName=Baby::getBabyById(getBabyId()).getName();
    return QString(QObject::tr("%0 was given to %1 at %2")).
            arg(getMedicineName()).
            arg(babyName).
            arg(getStartDate().toString("hh:mm"));
}

QString MedicineEvent::getIcon()
{
    return ICON;
}

PEvent MedicineEvent::clone()
{
    MedicineEvent* medEvent=new MedicineEvent();
    PEvent event=PEvent(medEvent);
    QString medName=getMedicineName();
    QString notes=getNotes();

    medEvent->setMedicineName(medName);
    medEvent->setNotes(notes);

    return event;
}

bool MedicineEvent::isRecurrentAble()
{
    return true;
}
