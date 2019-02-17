#include "medicineevent.h"
#include <QStringList>
#include <QString>
#include <QApplication>
#include "baby.h"

MedicineEvent::MedicineEvent() : Event()
{
    QString notes="|";
    Event::setNotes(notes);
}

QString MedicineEvent::getMedicineName()
{
    return Event::getNotes().split("|").at(0);
}

void MedicineEvent::setMedicineName(QString &medicineName)
{
    QString notes=medicineName+"|"+getNotes();
    Event::setNotes(notes);
}

QString MedicineEvent::getNotes()
{
    return Event::getNotes().split("|").at(1);
}

void MedicineEvent::setNotes(QString &notes)
{
    QString newNotes=getMedicineName()+"|"+notes;
    Event::setNotes(newNotes);
}


QString MedicineEvent::getShortDesc()
{
    QString eventData;

    eventData=getMedicineName()+QApplication::tr(" at: ")+getStartDate().toString("hh:mm");

    return eventData;
}

QString MedicineEvent::getAlarmDesc()
{
    QString babyName=Baby::getBabyById(getBabyId()).getName();
    return QApplication::tr("It's time to give ")+getMedicineName()+QApplication::tr(" to ")+babyName;
}

QString MedicineEvent::getNotfDesc()
{
    QString babyName=Baby::getBabyById(getBabyId()).getName();
    return QString(QApplication::tr("%0 was given to %1 at %2")).
            arg(getMedicineName()).
            arg(babyName).
            arg(QTime::currentTime().toString("hh:mm"));
}
