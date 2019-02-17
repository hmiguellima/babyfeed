#include <e32std.h>
#include "xqalarms.h"
#include "xqalarms_p.h"

const uint KClockAlarm = 270498106;

XQAlarmsPrivate::XQAlarmsPrivate(XQAlarms *qq) : q(qq)
{
    iError = iSession.Connect();
}

XQAlarmsPrivate::~XQAlarmsPrivate()
{
    iSession.Close();
}

XQAlarm XQAlarmsPrivate::alarm(int alarmId) const
{
    XQAlarm alarmData;
    
    TRAP(iError,
        TASShdAlarm alarm;
        User::LeaveIfError(iSession.GetAlarmDetails(alarmId, alarm));
        
        TPtrC message = alarm.Message();
        QString string = QString::fromUtf16(message.Ptr(), message.Length());
        alarmData.setMessage(string);
        
        // Date and time
        TDateTime alarmExpiryDateTime = alarm.OriginalExpiryTime().DateTime();
        QDateTime alarmDataExpiryDateTime(
                QDate(alarmExpiryDateTime.Year(),
                alarmExpiryDateTime.Month()+1,
                alarmExpiryDateTime.Day()+1),
                QTime(alarmExpiryDateTime.Hour(),
                alarmExpiryDateTime.Minute(),
                0,
                0));
        alarmData.setExpiryTime(alarmDataExpiryDateTime);
        
        TAlarmCategory category;
        User::LeaveIfError(iSession.GetAlarmCategory(alarmId, category));
        alarmData.setCategory(category.iUid);
        
        alarmData.setRepeatDefinition(static_cast<XQAlarm::RepeatDefinition>
                (alarm.RepeatDefinition()));
        alarmData.m_id = alarmId;
        
        // Date and time
        TDateTime alarmNDTDateTime = alarm.NextDueTime().DateTime();
        QDateTime alarmDataNDTDateTime(
                QDate(alarmNDTDateTime.Year(),
                alarmNDTDateTime.Month()+1,
                alarmNDTDateTime.Day()+1),
                QTime(alarmNDTDateTime.Hour(),
                alarmNDTDateTime.Minute(),
                alarmNDTDateTime.Second(),
                0));
        alarmData.m_nextDueTime = alarmDataNDTDateTime;
    )
    
    return alarmData;
}

QList<int> XQAlarmsPrivate::alarmIds() const
{
    QList<int> idList;
    
    RArray<TAlarmId> ids;
    
    // Get List of all alarms
    TRAP(iError,
        iSession.GetAlarmIdListL(ids);
        )
    if (iError != KErrNone)
    {
        return idList;
    }
    TASShdAlarm alarm;
    
    for(TInt i = 0; i<ids.Count(); i++)
    {
        iError = iSession.GetAlarmDetails(ids[i], alarm);
        if (iError != KErrNone)
        {
            return QList<int>();
        }
        idList.append(ids[i]);
    }
    return idList;
}

bool XQAlarmsPrivate::addAlarm(XQAlarm& alarmData)
{
    TASShdAlarm alarm;
        
    QString messageString = alarmData.message();
    messageString = messageString.left(KMaxAlarmMessageLength);
    TAlarmMessage& message(alarm.Message());
    message.Copy(reinterpret_cast<const TUint16*>(messageString.utf16()));
    
    // Date and time
    QDateTime alarmDataDateTime = alarmData.expiryTime();
    QDate startDate = alarmDataDateTime.date();
    QTime startTime = alarmDataDateTime.time();
    
    TDateTime alarmDateTime(
            startDate.year(),
            static_cast<TMonth>(startDate.month()-1),
            startDate.day()-1,
            startTime.hour(),
            startTime.minute(),
            startTime.second(),
            0);
    alarm.OriginalExpiryTime() = alarmDateTime;
    TTime& ndt = alarm.NextDueTime();
    ndt = alarmDateTime;
    
    TDateTime alarmExpiryDateTime = alarm.OriginalExpiryTime().DateTime();
    
    if (alarmData.category() == -1)
    {
        alarm.Category() = TAlarmCategory::Uid(KClockAlarm);
    }
    else
    {
        alarm.Category() = TAlarmCategory::Uid(alarmData.category());
    }
    
    TAlarmRepeatDefinition& alarmRepeatDefinition = alarm.RepeatDefinition();
    alarmRepeatDefinition = static_cast<TAlarmRepeatDefinition>
            (alarmData.repeatDefinition());

    iError = iSession.AlarmAdd(alarm);
    if (iError == KErrNone)
    {
        alarmData.m_id = alarm.Id();
    }
    return (iError == KErrNone);
}

bool XQAlarmsPrivate::setEnabled(int alarmId, bool status)
{
    iError = iSession.SetAlarmStatus(alarmId, static_cast<TAlarmStatus>(!status));
    return (iError == KErrNone);
}

bool XQAlarmsPrivate::isEnabled(int alarmId) const
{
    TAlarmStatus status;
    iError = iSession.GetAlarmStatus(alarmId, status);
    return !static_cast<bool>(status);
}

bool XQAlarmsPrivate::deleteAlarm(int alarmId)
{
    iError = iSession.AlarmDelete(alarmId);
    return (iError == KErrNone);
}

XQAlarms::Error XQAlarmsPrivate::error() const
{
    switch (iError)
    {
        case KErrNone:
            return XQAlarms::NoError;
        case KErrNoMemory:
            return XQAlarms::OutOfMemoryError;
        case KErrNotFound:
            return XQAlarms::NotFoundError;
        case KErrCouldNotConnect:
            return XQAlarms::CouldNotConnectError;
        case KErrAccessDenied:
            return XQAlarms::AccessDeniedError;
        default:
            return XQAlarms::UnknownError;
    }
}
