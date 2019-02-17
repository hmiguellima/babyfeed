#ifndef MEDICINEEVENT_H
#define MEDICINEEVENT_H

#include "event.h"

class MedicineEvent : public BabyEvent
{
public:
    static const QString ICON;

    MedicineEvent();

    QString getShortDesc();
    QString getAlarmDesc();
    QString getMedicineName();
    void setMedicineName(QString &medicineName);
    QString getNotes();
    void setNotes(QString &notes);
    QString getNotfDesc();
    QString getIcon();
    PEvent clone();
    bool isRecurrentAble();

private:
};

#endif // MEDICINEEVENT_H
