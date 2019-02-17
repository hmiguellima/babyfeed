#ifndef MEDICINEEVENT_H
#define MEDICINEEVENT_H

#include "event.h"

class MedicineEvent : public Event
{
public:
    MedicineEvent();

    QString getShortDesc();
    QString getAlarmDesc();
    QString getMedicineName();
    void setMedicineName(QString &medicineName);
    QString getNotes();
    void setNotes(QString &notes);
    QString getNotfDesc();
};

#endif // MEDICINEEVENT_H
