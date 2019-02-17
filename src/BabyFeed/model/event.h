#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDateTime>
#include <QList>
#include <QSharedPointer>
#include <QDate>
#include <QWidget>
#include <QPlainTextEdit>

#define PEvent QSharedPointer<Event>
#define MAX_NOTIFICATION_LAG_SECS 1800

class Baby;

class Event : public QWidget
{
    Q_OBJECT
public:
    enum {
        LEFT_BREAST,
        BOTTLE,
        RIGHT_BREAST,
        POTTY,
        MEDICINE,
        MEASURE
    };
    static const char TYPE_LEFT_BREAST='L';
    static const char TYPE_BOTTLE='B';
    static const char TYPE_RIGHT_BREAST='R';
    static const char TYPE_MEDICINE='M';
    static const char TYPE_POTTY='P';
    static const char TYPE_MEASURE='W';

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
    void setAlarmNativeKey(QString key);
    QString getAlarmNativeKey();
    bool isChecked();
    void setChecked(bool checked);
    void setHeight(int height);
    int getHeight();
    void setWeight(int weight);
    int getWeight();
    void setCephalic(int cephalic);
    int getCephalic();

    virtual void setNotes(QString &notes);
    virtual QString getNotes();
    virtual QString getIcon()=0;
    virtual void persist();
    void remove();
    virtual QString getShortDesc()=0;
    virtual QString getAlarmDesc()=0;
    virtual QString getNotfDesc()=0;
    static QList<PEvent> list(Baby &baby, QDate startDate, QDate endDate, QString filter);
    static QList<PEvent> list(Baby &baby, QDate startDate, QDate endDate, QString filter, int maxRecords);
    static QDate getMinFeedEventDate(Baby &baby);
    static QDate getMaxFeedEventDate(Baby &baby);
    static QDate getMinMeasurementEventDate(Baby &baby);
    static QDate getMaxMeasurementEventDate(Baby &baby);
    virtual bool isEmpty();
    virtual bool isRecurrentAble();
    virtual bool hasDuration();
    virtual PEvent clone()=0;
    void setAlarm(QDateTime start, QDateTime end, QString message);
    static void setTimerAlarm(QDateTime start, QString message);
    static int getNextRecurrenceId();
    static void deleteExpiredAlarms();
    static void removeAlarm(QString id, QDate date);
    static int getTypeIndex(char type);
    static char getTypeFromIndex(int index);
    QString getTypeName();

protected:
    char type;

private:
    int id;
    int babyId;
    int recurrenceId;
    int alarmNativeId;
    QString alarmNativeKey;
    bool checked;
    QString notes;
    int duration;
    QDateTime startDate;
    int height;
    int weight;
    int cephalic;
};

#endif // EVENT_H
