#ifndef MEDICINEEVENT_H
#define MEDICINEEVENT_H

#include "event.h"
#include <QLineEdit>

class MedicineEvent : public Event
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
    QLineEdit *drugEdit;
    QPlainTextEdit *drugNotesEdit;
};

#endif // MEDICINEEVENT_H
