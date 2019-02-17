#ifndef XQALARMS_H
#define XQALARMS_H

// INCLUDES
#include <QObject>
#include <QDateTime>
#include "alarms_global.h"

// FORWARD DECLARATIONS
class XQAlarm;
class XQAlarmsPrivate;

// CLASS DECLARATION
class XQALARMS_EXPORT XQAlarms : public QObject
{
public:
    XQAlarms(QObject* parent = 0);
    ~XQAlarms();
    
public:
    enum Error
    {
        NoError = 0,
        OutOfMemoryError,
        NotFoundError,
        CouldNotConnectError,
        AccessDeniedError,
        UnknownError = -1
    };
    
    enum Weekday
    {
        Monday = 1,
        Tuesday = 2,
        Wednesday = 4,
        Thursday = 8,
        Friday = 16,
        Saturday = 32,
        Sunday = 64
    };
    
    XQAlarm alarm(int alarmId) const;
    QList<int> alarmIds() const;
    
    bool addAlarm(XQAlarm& alarmData);
    bool deleteAlarm(int alarmId);
    
    bool setEnabled(int alarmId, bool status);
    bool isEnabled(int alarmId) const;
    
    XQAlarms::Error error() const;
    
private:
    XQAlarmsPrivate* d;
};

class XQALARMS_EXPORT XQAlarm
{
public:
    
	enum RepeatDefinition
    {
        RepeatOnce = 0,
        RepeatNext24Hours,
        RepeatDaily,
        RepeatWorkdays,
        RepeatWeekly
	};
    
    XQAlarm();
    ~XQAlarm();
    
    int id() const;
    
    void setMessage(const QString& message);
    QString message() const;
    
    void setExpiryTime(const QDateTime& expiryTime);
    QDateTime expiryTime() const;
    
    QDateTime nextDueTime() const;
    
    void setCategory(int category);
    int category() const;
    
    void setRepeatDefinition(XQAlarm::RepeatDefinition repeatDefinition);
    XQAlarm::RepeatDefinition repeatDefinition() const;
    
private:
    int m_id;
    QDateTime m_expiryTime;
    QDateTime m_nextDueTime;
    QString m_message;
    int m_category;
    XQAlarm::RepeatDefinition m_repeatDefinition;
    friend class XQAlarmsPrivate;
};

#endif // XQALARMS_H

// End of file
