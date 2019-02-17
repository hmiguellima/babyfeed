#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDateTime>
#include <QList>
#include <QSharedPointer>
#include <QDate>

#define PEvent QSharedPointer<Event>

class Baby;

class Event
{
public:
    Event();

    int getId();
    char getType();

    void setType(char type);
    QDateTime getStartDate();
    void setStartDate(QDateTime startDate);
    int getDuration();
    void setDuration(int duration);
    int getBabyId();
    void setBabyId(int babyId);
    void setRecurrenceId(int id);
    int getRecurrenceId();
    void setAlarmNativeId(int alarmNativeId);
    int getAlarmNativeId();
    bool isChecked();
    void setChecked(bool checked);
    virtual void setNotes(QString &notes);
    virtual QString getNotes();

    void persist();
    void remove();
    virtual QString getShortDesc()=0;
    virtual QString getAlarmDesc()=0;
    virtual QString getNotfDesc()=0;
    static QList<PEvent> list(Baby &baby, QDate &startDate, QDate &endDate);
    virtual bool isEmpty();
    void setAlarm(QDateTime dateTime, QString message);
    static int getNextRecurrenceId();

protected:
    static void removeAlarm(int id);

private:
    int id;
    int babyId;
    int recurrenceId;
    int alarmNativeId;
    bool checked;
    char type;
    QString notes;
    int duration;
    QDateTime startDate;
};

#endif // EVENT_H
